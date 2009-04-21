/*
 * Copyright (c) 2009 LAAS/CNRS
 * All rights reserved.
 *
 * Redistribution and use  in source  and binary  forms,  with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   1. Redistributions of  source  code must retain the  above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice,  this list of  conditions and the following disclaimer in
 *      the  documentation  and/or  other   materials provided  with  the
 *      distribution.
 *
 * THIS  SOFTWARE IS PROVIDED BY  THE  COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND  ANY  EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES  OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR  PURPOSE ARE DISCLAIMED. IN  NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR      CONTRIBUTORS  BE LIABLE FOR   ANY    DIRECT, INDIRECT,
 * INCIDENTAL,  SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE   OF THIS SOFTWARE, EVEN   IF ADVISED OF   THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#include "pythoninterpreter.h"

#include <iostream>
#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
// #include "ptr_map_indexing_suite.hpp"

#include "ast.h"

using namespace G3nom;
using namespace std;
using namespace boost::python;

PythonInterpreter* PythonInterpreter::m_instance = 0;

/********************** Python module definition ********/

void writeStdout(const char *text)
{
	PythonInterpreter::getInstance()->writeStdout(text);
}

BOOST_PYTHON_MODULE_INIT(Logger)
{
  def("write", &writeStdout);
}

Component* pygetCurrentComponent()
{
	PythonInterpreter *i = PythonInterpreter::getInstance();
	return i->component();
}

BOOST_PYTHON_MODULE_INIT(G3nom)
{
	def("getComponent", &pygetCurrentComponent, return_value_policy<reference_existing_object>());

	class_<Component>("Component")
	.def("name", &Component::name)
	.def("task", &Component::task, return_value_policy<reference_existing_object>())
	.def("debug", &Component::debug)
	.def("tasksList", &Component::tasksList)
	.def("tasksMap", &Component::tasksMap, return_value_policy<reference_existing_object>());

	class_<Task, Task::Ptr>("Task")
	.def("debug", &Task::debug)
	.def_readonly("priority", &Task::priority);

	// vector of strings
	class_<std::vector<std::string> >("StringVec")
	.def(vector_indexing_suite<std::vector<std::string> >());

	class_<Task::Map>("TaskMap")
	.def(map_indexing_suite<Task::Map, true>());
}

/********************** Python interpreter ********/

// allocates a new string using new [], and copies contents into it..
static char* newString(const char* contents)
{
	char* ret = new char[strlen(contents) + 1];
	strcpy(ret, contents);
	return ret;
}

namespace G3nom
{
class PythonInterpreterPrivate
{
	public:
		boost::python::object pydict;
		std::string outbuf;
};
}

// See Kig source (part of KDE EDU module) for an example
// of how to use embedded python (or Kalzium for more advanced stuff)
PythonInterpreter::PythonInterpreter()
		: d(new PythonInterpreterPrivate())
{
	char *s = newString("G3nom"); // we can't delete this string
	char *ss = newString("Logger"); // we can't delete this string
	PyImport_AppendInittab(s, initG3nom);
	PyImport_AppendInittab(ss, initLogger);
	Py_Initialize();

	// create global dict object
	object main = import("__main__");
	d->pydict = main.attr("__dict__");
	// import our module
	interpret("import G3nom;\nfrom G3nom import *;\n");
	interpret("import Logger");
	interpret("import sys\nsys.stdout = Logger");
}

PythonInterpreter::~PythonInterpreter()
{}

PythonInterpreter* PythonInterpreter::getInstance()
{
	if (!m_instance)
		m_instance = new PythonInterpreter();
	return m_instance;
}

void PythonInterpreter::start(G3nom::Component* c)
{
	m_component = c;
	interpret("comp = getComponent()\n");
}

std::string PythonInterpreter::interpret(const std::string& s)
{
	try {
		d->outbuf.erase();
		exec(str(s), d->pydict, d->pydict);
		return d->outbuf.substr(0, d->outbuf.length() - 1);
	} catch (error_already_set const &) {
		cerr << "Error in python interpreter: ";
		PyErr_Print();
		cerr << endl;
	}
}

std::string PythonInterpreter::eval(const std::string& s)
{
	return interpret("print " + s);
}

void PythonInterpreter::exportVar(const std::string &name, const std::string &value)
{
	interpret(name + " = " + value);
}

void PythonInterpreter::writeStdout(const char *text)
{
	d->outbuf.append(text);
}

// kate: indent-mode cstyle; replace-tabs off; tab-width 4; 
