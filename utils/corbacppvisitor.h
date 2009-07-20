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
#ifndef G3NOM_CORBA_CPPVISITOR_H
#define G3NOM_CORBA_CPPVISITOR_H

#include "typevisitor.h"
#include "idltype.h"

namespace G3nom
{
namespace Idl {

/** \short A visitor for CORBA C++

* This visitor is tweaked to do what the openRTM template expects. For instance,
* all identifiers are suffixed with "_Corba".
* You should not create an object of this type. Instead, use the static #mapTypeToCpp()
* and #mapValueToCpp() that directly output a string.
*/
class CorbaCppVisitor : public TypeVisitor
{
	public:
		CorbaCppVisitor(std::ostream &out, bool declOnly, bool isOutType) 
		: m_out(out), m_declOnly(declOnly), m_isOutType(isOutType) {}
		virtual ~CorbaCppVisitor() {}

		/** Print the C++ mapping of the type. The \a declOnly argument is used
		* to indicate wheter to print the full definition of the type or just a declaration (ie its name). 
		* The \a out indicates whether the type is used as a return value, in which case the mapping can be
		* different. */
		static std::string mapTypeToCpp(IdlType::Ptr t, bool declOnly=false, bool out=false);
		/** Print the C++ mapping of the const value. They are mapped to global const variables. */
		static std::string mapValueToCpp(ConstValue *v);

		virtual void visitBaseType(BaseType*);
		virtual void visitStringType(StringType*);
		virtual void visitWStringType(WStringType*);
		virtual void visitSequenceType(SequenceType*);
		virtual void visitFixedType(FixedType*);
		virtual void visitStructType(StructType*);
		virtual void visitTypedefType(TypedefType*);
		virtual void visitEnumType(EnumType*);
		virtual void visitArrayType(ArrayType *);
		virtual void visitNamedType(NamedType*);

		virtual void visitConstValue(ConstValue *v);

	protected:
		std::ostream &m_out;
		bool m_declOnly;
		bool m_isOutType;
		std::string m_indent;
};

}
}

#endif

// kate: indent-mode cstyle; replace-tabs off; tab-width 4;  replace-tabs off;
