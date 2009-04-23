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

#include "idltype.h"

#include <iostream>

using namespace G3nom;
using namespace Idl;
using namespace std;

IdlType::IdlType(Kind k)
		: m_kind(k)
{
}

string IdlType::kindAsString() const
{
	switch (m_kind) {
		case Null:
			return "null";
		case Void:
			return "void";
		case Short:
			return "short";
		case Long:
			return "long";
		case LongLong:
			return "long long";
		case UShort:
			return "unsigned short";
		case ULong:
			return "unsigned long";
		case ULongLong:
			return "unsigned long long";
		case Float:
			return "float";
		case Double:
			return "double";
		case LongDouble:
			return "long double";
		case Fixed:
			return "fixed";
		case Boolean:
			return "boolean";
		case Char:
			return "char";
		case WChar:
			return "wchar";
		case Octet:
			return "octet";
		case Any:
			return "any";
		case Struct:
			return "struct";
		case Union:
			return "union";
		case Enum:
			return "enum";
		case String:
			return "string";
		case WString:
			return "wstring";
		case Sequence:
			return "sequence";
			//   case Array:	return "array";
		case Typedef:
			return "typedef";
		default:
			return "unknown";
	}
}

// IdlType* IdlType::unalias()
// {
// 	IdlType* t = this;
// 	while (t && t->kind() == Typedef) {
// //     if (((Declarator*)((DeclaredType*)t)->decl())->sizes())
// // 	break;
// //     t = ((Declarator*)((DeclaredType*)t)->decl())->alias()->aliasType();
// 		t = static_cast<TypedefType*>(t)->aliasType()->get();
// 	}
// 	return IdlType::Ptr(t);
// }


// IdlType* IdlType::scopedNameToType(const char* file, int line, const ScopedName* sn)
// {
//   const Scope::Entry* se = Scope::current()->findForUse(sn, file, line);
//
//   if (se) {
//     if (se->kind() == Scope::Entry::E_DECL) {
//       IdlType *t = se->idltype();
//       if (t) return t;
//     }
//     char* ssn = sn->toString();
//     IdlError(file, line, "'%s' is not a type", ssn);
//     IdlErrorCont(se->file(), se->line(), "('%s' declared here)", ssn);
//     delete [] ssn;
//   }
//   return 0;
// }

// Static type object pointers
BaseType::Ptr BaseType::nullType = IdlType::Ptr(new BaseType(IdlType::Null));
BaseType::Ptr BaseType::voidType = IdlType::Ptr(new BaseType(IdlType::Void));
BaseType::Ptr BaseType::shortType = IdlType::Ptr(new BaseType(IdlType::Short));
BaseType::Ptr BaseType::longType = IdlType::Ptr(new BaseType(IdlType::Long));
BaseType::Ptr BaseType::longlongType = IdlType::Ptr(new BaseType(IdlType::LongLong));
BaseType::Ptr BaseType::ushortType = IdlType::Ptr(new BaseType(IdlType::UShort));
BaseType::Ptr BaseType::ulongType = IdlType::Ptr(new BaseType(IdlType::ULong));
BaseType::Ptr BaseType::ulonglongType = IdlType::Ptr(new BaseType(IdlType::ULongLong));
BaseType::Ptr BaseType::floatType = IdlType::Ptr(new BaseType(IdlType::Float));
BaseType::Ptr BaseType::doubleType = IdlType::Ptr(new BaseType(IdlType::Double));
BaseType::Ptr BaseType::longdoubleType = IdlType::Ptr(new BaseType(IdlType::LongDouble));
BaseType::Ptr BaseType::booleanType = IdlType::Ptr(new BaseType(IdlType::Boolean));
BaseType::Ptr BaseType::charType = IdlType::Ptr(new BaseType(IdlType::Char));
BaseType::Ptr BaseType::wcharType = IdlType::Ptr(new BaseType(IdlType::WChar));
BaseType::Ptr BaseType::octetType = IdlType::Ptr(new BaseType(IdlType::Octet));
BaseType::Ptr BaseType::anyType = IdlType::Ptr(new BaseType(IdlType::Any));
BaseType::Ptr StringType::unboundedStringType = IdlType::Ptr(new StringType(0));
BaseType::Ptr WStringType::unboundedWStringType = IdlType::Ptr(new WStringType(0));

/************ Declarator ***************/

void Declarator::addBound(int b)
{
	m_bounds.push_back(b);
}

bool Declarator::isArray() const
{
	return !m_bounds.empty();
}

/************ StructType ***************/

void StructType::addMember(IdlType::Ptr t, Declarator::VectPtr v)
{
	m_members.push_back(make_pair(t, v));
}

IdlType::Ptr StructType::member(const std::string &name) 
{
	vector<TypeDeclarator>::const_iterator it = m_members.begin();
	for(; it != m_members.end(); ++it) {
		Declarator::Vect::const_iterator it2 = it->second->begin();
		for(; it2 != it->second->end(); ++it2) {
			if((*it2)->identifier() == name)
				return it->first;
		}
	}
}

/************ EnumType ***************/

void EnumType::addEnumerator(const std::string &e)
{
	m_enum.push_back(e);
}

/************ TypedefType ***************/

bool TypedefType::hasIdentifier(const std::string &name)
{
	Declarator::Vect::const_iterator it = m_declarators->begin();
	for (; it != m_declarators->end(); ++it) {
		if ((*it)->identifier() == name)
			return true;
	}
	return false;
}

// kate: indent-mode cstyle; replace-tabs off; tab-width 4;  replace-tabs off;  replace-tabs off;  replace-tabs off;