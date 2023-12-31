/*
 * Copyright (c) 2010-2014,2017-2018,2020,2022 LAAS/CNRS
 * All rights reserved.
 *
 * Redistribution  and  use  in  source  and binary  forms,  with  or  without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of  source  code must retain the  above copyright
 *      notice and this list of conditions.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice and  this list of  conditions in the  documentation and/or
 *      other materials provided with the distribution.
 *
 * THE SOFTWARE  IS PROVIDED "AS IS"  AND THE AUTHOR  DISCLAIMS ALL WARRANTIES
 * WITH  REGARD   TO  THIS  SOFTWARE  INCLUDING  ALL   IMPLIED  WARRANTIES  OF
 * MERCHANTABILITY AND  FITNESS.  IN NO EVENT  SHALL THE AUTHOR  BE LIABLE FOR
 * ANY  SPECIAL, DIRECT,  INDIRECT, OR  CONSEQUENTIAL DAMAGES  OR  ANY DAMAGES
 * WHATSOEVER  RESULTING FROM  LOSS OF  USE, DATA  OR PROFITS,  WHETHER  IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR  OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *                                           Anthony Mallet on Fri Jan 22 2010
 */
#include "acgenom.h"

#include <assert.h>
#include <libgen.h>
#include <string.h>

#include <tcl.h>

#include "genom.h"
#include "engine.h"


/* --- local data ---------------------------------------------------------- */

static Tcl_Obj *	member_list(Tcl_Interp *interp, idltype_s t,
				Tcl_Obj *pattern);


/* --- type command -------------------------------------------------------- */

/*/
 * == *$type* TCL engine command
 *
 * Those commands manipulate IDL type objects and return information about
 * them. They all take a type object as their first argument, noted `$type` in
 * the following command descriptions. Such an object is typically returned by
 * other procedures, such as
 * link:cmd-dotgen{outfilesuffix}#dotgen_types[`dotgen types`].
 */
int
type_cmd(ClientData v, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
  enum typeidx {
    typeidx_kind, typeidx_name, typeidx_fullname, typeidx_scope, typeidx_fixed,
    typeidx_final, typeidx_parent, typeidx_nested, typeidx_types, typeidx_type,
    typeidx_length, typeidx_value, typeidx_valuekind, typeidx_members,
    typeidx_discriminator, typeidx_port, typeidx_remote, typeidx_cname,
    typeidx_mangle, typeidx_mapping, typeidx_declarator, typeidx_address,
    typeidx_deref, typeidx_argument, typeidx_retval, typeidx_pass,
    typeidx_digest, typeidx_masquerade, typeidx_loc, typeidx_class
  };
  static const char *args[] = {
    [typeidx_kind] = "kind", [typeidx_name] = "name",
    [typeidx_fullname] = "fullname", [typeidx_scope] = "scope",
    [typeidx_fixed] = "fixed", [typeidx_final] = "final",
    [typeidx_parent] = "parent", [typeidx_nested] = "nested",
    [typeidx_types] = "types", [typeidx_type] = "type",
    [typeidx_length] = "length", [typeidx_value] = "value",
    [typeidx_valuekind] = "valuekind", [typeidx_members] = "members",
    [typeidx_discriminator] = "discriminator", [typeidx_port] = "port",
    [typeidx_remote] = "remote", [typeidx_cname] = "cname",
    [typeidx_mangle] = "mangle", [typeidx_mapping] = "mapping",
    [typeidx_declarator] = "declarator", [typeidx_address] = "address",
    [typeidx_deref] = "dereference", [typeidx_argument] = "argument",
    [typeidx_retval] = "return-value", [typeidx_pass] = "pass",
    [typeidx_digest] = "digest", [typeidx_masquerade] = "masquerade",
    [typeidx_loc] = "loc", [typeidx_class] = "class", NULL
  };
  idltype_s t = v;
  Tcl_Obj *r = NULL;
  int s;

  int i = typeidx_fullname; /* return full name by default */

  if (objc > 1) {
    s = Tcl_GetIndexFromObj(interp, objv[1], args, "subcommand", 0, &i);
    if (s != TCL_OK) return s;
  }
  if (i == typeidx_members) {
    /* 'members' subcommand can have one additional parameter */
    if (objc > 3) {
      Tcl_WrongNumArgs(interp, 2, objv, "?pattern?");
      return TCL_ERROR;
    }
  } else if (i == typeidx_types) {
    /* 'types' subcommand can have one additional parameter */
    if (objc > 3) {
      Tcl_WrongNumArgs(interp, 2, objv, "?filter?");
      return TCL_ERROR;
    }
  } else if (i == typeidx_declarator || i == typeidx_address) {
    /* 'declarator' and 'address' subcommands can have one additional
     * parameter */
    if (objc > 3) {
      Tcl_WrongNumArgs(interp, 2, objv, "?var?");
      return TCL_ERROR;
    }
  } else if (i == typeidx_masquerade) {
    /* 'masquerade' subcommand can have one additional parameter */
    if (objc > 3) {
      Tcl_WrongNumArgs(interp, 2, objv, "?template?");
      return TCL_ERROR;
    }
  } else if (i == typeidx_argument || i == typeidx_retval ||
             i == typeidx_pass || i == typeidx_deref) {
    /* 'argument', 'return-value', 'pass' and 'deref' subcommands can have two
     * additional parameters */
    if (objc < 3 || objc > 4) {
      Tcl_WrongNumArgs(interp, 2, objv, "kind ?var?");
      return TCL_ERROR;
    }
  } else if (i == typeidx_loc) {
    if (objc > 3) {
      Tcl_WrongNumArgs(interp, 2, objv, "?element?");
      return TCL_ERROR;
    }
  } else {
    if (objc > 2) {
      Tcl_WrongNumArgs(interp, 1, objv, "subcommand");
      return TCL_ERROR;
    }
  }
  switch((enum typeidx)i) {
    /*/
     * [[kind]]
     * === *$type kind*
     *
     * Return a string describing the nature of the IDL type, such as `long`,
     * `double`, `struct` ...
     */
    case typeidx_kind:
      r = Tcl_NewStringObj(type_strkind(type_kind(t)), -1);
      break;

    /*/
     * [[name]]
     * === *$type name*
     *
     * Return the name of the IDL type. No namespace components are included in
     * the result.
     */
    case typeidx_name:
      r = type_name(t) ? Tcl_NewStringObj(type_name(t), -1) : NULL;
      break;

    /*/
     * [[fullname]]
     * === *$type fullname*
     *
     * Return the fully qualified name of the IDL type. The result includes
     * the namespace hierarchy in which the type is defined and the last
     * component is the result of `$type name`.
     */
    case typeidx_fullname:
      r = type_fullname(t) ? Tcl_NewStringObj(type_fullname(t), -1) : NULL;
      break;

    /*/
     * [[scope]]
     * === *$type scope*
     *
     * Return the list of lexical scopes in which the type is defined. Each
     * element of the list contains two values: the nature of the scope and its
     * name. The nature of the scope will be either `module` for IDL modules,
     * or `struct` if the type is defined inside an IDL `struct`.
     */
    case typeidx_scope: {
      scope_s s = type_scope(t);
      Tcl_Obj *n[2], *l;

      r = Tcl_NewListObj(0, NULL);
      for (s = type_scope(t); scope_parent(s); s = scope_parent(s)) {
	n[0] = Tcl_NewStringObj(scope_strkind(scope_kind(s)), -1);
	n[1] = Tcl_NewStringObj(scope_name(s), -1);
	l = Tcl_NewListObj(2, n);
	Tcl_ListObjReplace(interp, r, 0, 0, 1, &l);
      }
      break;
    }

    /*/
     * [[fixed]]
     * === *$type fixed*
     *
     * Return a boolean indicating if the type is of fixed, constant size
     * (true) or not (false).
     */
    case typeidx_fixed:
      r = Tcl_NewBooleanObj(type_fixed(t));
      break;

    /*/
     * [[final]]
     * === *$type final*
     *
     * Return a new type object with all aliases resolved. For `const` types,
     * this returns the type of the constant. For `typedef`, this return the
     * first non-aliased type. For `struct` and `union` members, this returns
     * the type of the member.
     */
    case typeidx_final:
      r = Tcl_NewStringObj(type_genref(type_final(t)), -1);
      break;

    /*/
     * [[parent]]
     * === *$type parent*
     *
     * Return the parent type of a nested type definition, or raise an error if
     * the type is not nested.
     */
    case typeidx_parent: {
      idltype_s p = type_parent(t);
      if (p) r = Tcl_NewStringObj(type_genref(p), -1);
      break;
    }

    /*/
     * [[nested]]
     * === *$type nested*
     *
     * Return the nested types defined by the given type
     */
    case typeidx_nested: {
      hiter i;

      r = Tcl_NewListObj(0, NULL);
      switch((int)type_kind(t)) {
        case IDL_STRUCT: case IDL_UNION: case IDL_EXCEPTION:
          for(hash_first(type_members(t), &i); i.current; hash_next(&i)) {
            if (type_kind(i.value) != IDL_MEMBER &&
                type_kind(i.value) != IDL_CASE &&
                type_kind(i.value) != IDL_ENUMERATOR)
              Tcl_ListObjAppendElement(
                interp, r, Tcl_NewStringObj(type_genref(i.value), -1));
          }
          break;
      }
      break;
    }

    /*/
     * [[types]]
     * === *$type types* ['filter']
     *
     * Return the list of all types that are recursively used by the given
     * type. In other words, this is the list of types that must be known in
     * order to completely define the given `$type`.
     *
     * For all basic types such as `long`, `double` and so forth, the returned
     * list is empty. For enumerated types, the result is the list of
     * enumerators. For aggregates such as `struct`, `union` or `exception`,
     * the result is the list of all members, expanded recursively with the
     * same rules. Finally, for `array`s or `sequence`s, this returns the type
     * of the array or sequence elements, recursively expanded.
     *
     * .Arguments
     * [horizontal]
     * 'filter'::
     * The optional filter can be used to filter out some elements from the
     * type list. The filter must be a tcl anonymous function (see tcl
     * `[apply]` command) that accepts one argument that is a genom object. It
     * must return a boolean to indicate whether the type should be included
     * (true) or excluded (false).
     */
    case typeidx_types: {
      Tcl_Obj *argv[] = {
        Tcl_NewStringObj("object", -1),
        objv[1],
        objv[0],
        Tcl_NewStringObj("public", -1),
        objc>2 ? objv[2]:NULL
      };

      Tcl_IncrRefCount(argv[0]);
      Tcl_IncrRefCount(argv[3]);
      s = Tcl_EvalObjv(interp, objc + 2, argv, TCL_EVAL_GLOBAL);
      Tcl_DecrRefCount(argv[3]);
      Tcl_DecrRefCount(argv[0]);
      if (s != TCL_OK) return TCL_ERROR;
      r = Tcl_GetObjResult(interp);
      break;
    }

    /*/
     * [[type]]
     * === *$type type*
     *
     * Return the underlying type of a type that contains another type
     * definition. For instance, this procedure invoked on an `array` or
     * `sequence` type returns the element type. It returns the aliased type
     * for `typedef`.
     */
    case typeidx_type:
      switch((int)type_kind(t)) {
	case IDL_ENUMERATOR: case IDL_SEQUENCE: case IDL_OPTIONAL:
        case IDL_ARRAY: case IDL_CONST: case IDL_TYPEDEF: case IDL_MEMBER:
        case IDL_CASE: case IDL_FORWARD_STRUCT: case IDL_FORWARD_UNION:
	  r = Tcl_NewStringObj(type_genref(type_type(t)), -1);
	  break;
      }
      break;

    /*/
     * [[length]]
     * === *$type length*
     *
     * Return the length of an `array`, `sequence` or `string` type.
     */
    case typeidx_length:
      switch((int)type_kind(t)) {
	case IDL_SEQUENCE: case IDL_ARRAY: case IDL_STRING:
	  if (type_length(t) != -1U) {
	    r = Tcl_NewIntObj(type_length(t));
	    break;
	  }
      }
      break;

    /*/
     * [[value]]
     * === *$type value*
     *
     * Return the value associated with a `const` type.
     */
    case typeidx_value:
      switch((int)type_kind(t)) {
	case IDL_CONST:
	  r = Tcl_NewStringObj(const_strval(type_constvalue(t)), -1);
	  break;

        case IDL_CASE: {
          clist_s values = type_casevalues(t);
          citer i;

          r = Tcl_NewListObj(0, NULL);
          for(clist_first(values, &i); i.current; clist_next(&i)) {
            Tcl_ListObjAppendElement(
              interp, r, Tcl_NewStringObj(const_strval(*i.value), -1));
          }
          break;
        }
      }
      break;

    /*/
     * [[valuekind]]
     * === *$type valuekind*
     *
     * Return the nature of the value associated with a `const` type.
     */
    case typeidx_valuekind:
      switch((int)type_kind(t)) {
        case IDL_CONST:
          r = Tcl_NewStringObj(const_strkind(type_constvalue(t).k), -1);
          break;
      }
      break;

    /*/
     * [[members]]
     * === *$type members*
     *
     * Return a list of types defined by the given `struct`, `union` or `enum`
     * type.
     */
    case typeidx_members:
      r = member_list(interp, t, objc > 2 ? objv[2] : NULL);
      break;

    /*/
     * [[discriminator]]
     * === *$type discriminator*
     *
     * Return the discriminator of the given `union`.
     */
    case typeidx_discriminator:
      switch((int)type_kind(t)) {
        case IDL_UNION:
          r = Tcl_NewStringObj(type_genref(type_discriminator(t)), -1);
          break;
      }
      break;

    /*/
     * [[port]]
     * === *$type port*
     *
     * Return the port object referenced by the given `port`.
     */
    case typeidx_port:
      switch((int)type_kind(t)) {
        case IDL_PORT:
          r = Tcl_NewStringObj(port_genref(type_port(t)), -1);
          break;
      }
      break;

    /*/
     * [[remote]]
     * === *$type remote*
     *
     * Return the remote object referenced by the given `remote`.
     */
    case typeidx_remote:
      switch((int)type_kind(t)) {
        case IDL_REMOTE:
          r = Tcl_NewStringObj(remote_genref(type_remote(t)), -1);
          break;
      }
      break;

    /*/
     * [[cname]]
     * === *$type cname*
     *
     * Return a string representing the type name in the current language.
     *
     * [[mangle]]
     * === *$type mangle*
     *
     * Return a string uniquely describing the given type, suitable for use as
     * an identifier in source code written in the current programming
     * language.
     *
     * [[mapping]]
     * === *$type mapping*
     *
     * Return an ASCII string representing the implementation (definition) of
     * the given type, suitable for use in source code written in the current
     * programming language.
     */
    case typeidx_cname:
    case typeidx_mangle:
    case typeidx_mapping: {
      Tcl_Obj *argv[] = {
        Tcl_NewStringObj("language::", -1),
        objv[0]
      };

      Tcl_IncrRefCount(argv[0]);
      Tcl_AppendStringsToObj(argv[0], args[i], NULL);
      s = Tcl_EvalObjv(interp, 2, argv, TCL_EVAL_GLOBAL);
      Tcl_DecrRefCount(argv[0]);
      if (s != TCL_OK) return TCL_ERROR;
      r = Tcl_GetObjResult(interp);
      break;
    }

    /*/
     * [[declarator]]
     * === *$type declarator* ['var']
     *
     * Return the declarator for $type or for a variable 'var' of that
     * type, in the current language.
     *
     * .Arguments
     * [horizontal]
     * 'var'::
     * The variable being declared. If not given, an abstract declarator is
     * returned.
     *
     * [[address]]
     * === *$type address* 'var'
     *
     * Return an expression representing the address of a variable of the given
     * type in the current language.
     *
     * .Arguments
     * [horizontal]
     * 'var'::
     * The variable of which the address must be taken.
     */
    case typeidx_declarator:
    case typeidx_address: {
      Tcl_Obj *argv[] = {
        Tcl_NewStringObj("language::", -1),
        objv[0],
        objv[2]
      };

      Tcl_IncrRefCount(argv[0]);
      Tcl_AppendStringsToObj(argv[0], args[i], NULL);
      s = Tcl_EvalObjv(interp, objc, argv, TCL_EVAL_GLOBAL);
      Tcl_DecrRefCount(argv[0]);
      if (s != TCL_OK) return TCL_ERROR;
      r = Tcl_GetObjResult(interp);
      break;
    }

    /*/
     * [[argument]]
     * === *$type argument* *value|reference* ['var']
     *
     * Return an expression that declares a parameter 'var' of the given
     * type, passed by value or reference according to the second parameter.
     *
     * .Arguments
     * [horizontal]
     * 'var'::
     * The argument name being declared. If not given, an abstract declarator
     * is returned.
     *
     * [[pass]]
     * === *$type pass* *value|reference* 'var'
     *
     * Return an expression that passes a variable 'var' of the given type
     * as a function parameter. The variable is passed by value or reference
     * according to second argument.
     *
     * .Arguments
     * [horizontal]
     * 'var'::
     * The variable that must be passed.
     *
     * [[dereference]]
     * === *$type dereference* *value|reference* 'var'
     *
     * Return an expression that retrieves the value of a parameter 'var',
     * passed by value or reference according to the second argument.
     *
     * .Arguments
     * [horizontal]
     * 'var'::
     * The argument name.
     */
    case typeidx_argument:
    case typeidx_retval:
    case typeidx_pass:
    case typeidx_deref: {
      Tcl_Obj *argv[] = {
        Tcl_NewStringObj("language::", -1),
        objv[0],
        objv[2],
        objv[3]
      };

      Tcl_IncrRefCount(argv[0]);
      Tcl_AppendStringsToObj(argv[0], args[i], NULL);
      s = Tcl_EvalObjv(interp, objc, argv, TCL_EVAL_GLOBAL);
      Tcl_DecrRefCount(argv[0]);
      if (s != TCL_OK) return TCL_ERROR;
      r = Tcl_GetObjResult(interp);
      break;
    }

    /*/
     * [[digest]]
     * === *$type digest*
     *
     * Return an ASCII representaion (32 characters) of an MD5 digest of the
     * given type. This is useful for implementing a cheap runtime verification
     * that two types match.
     */
    case typeidx_digest: {
      Tcl_Obj *argv[] = {
        Tcl_NewStringObj("object", -1),
        Tcl_NewStringObj("digest", -1),
        objv[0],
      };

      Tcl_IncrRefCount(argv[0]);
      Tcl_IncrRefCount(argv[1]);
      s = Tcl_EvalObjv(interp, 3, argv, TCL_EVAL_GLOBAL);
      Tcl_DecrRefCount(argv[1]);
      Tcl_DecrRefCount(argv[0]);
      if (s != TCL_OK) return TCL_ERROR;
      r = Tcl_GetObjResult(interp);
      break;
    }

    /*/
     * [[masquerade]]
     * === *$type masquerade*
     *
     * Return any value defined in a `#pragma masquerade` for that type,
     * if the current template matches the corresponding parameter of the
     * `#pragma`. See
     * link:../dotgen/pragma{outfilesuffix}#pragma_masquerade[`#pragma
     * masquerade`].
     */
    case typeidx_masquerade: {
      hash_s h;
      char *tmpl;
      char *masquerade;

      if (!type_fullname(t)) break;

      h = dotgen_hmasquerade();
      if (!h) break;

      if (objc < 3) {
        char name[PATH_MAX];

        strlcpy(name, runopt.tmpl, sizeof(name));
        tmpl = basename(name);
      } else
        tmpl = Tcl_GetString(objv[2]);
      if (!tmpl) break;

      h = hash_find(h, tmpl);
      if (!h) break;

      masquerade = hash_find(h, type_fullname(t));
      if (!masquerade) break;

      r = Tcl_NewStringObj(masquerade, -1);
      break;
    }

    /*/
     * [[loc]]
     * === *$type loc* [file|line|column|context]
     *
     * Return a list describing the source location where that type is
     * defined. The list contains four elements: the file name, the line
     * number, the column number and the original component context of the
     * definition. If an optional argument is given, only the corresponding
     * element is returned.
     */
    case typeidx_loc:
      r = tloc_item(interp, objc > 2 ? objv[2]:NULL, type_loc(t));
      if (!r) return TCL_ERROR;
      break;

    /*/
     * [[class]]
     * === *$type class*
     *
     * Always returns the string "type". Useful to determine at runtime
     * that the object is a type object.
     */
    case typeidx_class:
      r = Tcl_NewStringObj("type", -1);
      break;
  }

  if (!r) {
    Tcl_AppendResult(interp, "no such member \"", args[i], "\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, r);
  return TCL_OK;
}


/* --- member_list --------------------------------------------------------- */

/** return a Tcl list of type members, matching a pattern if not NULL.
*/
static Tcl_Obj *
member_list(Tcl_Interp *interp, idltype_s t, Tcl_Obj *pattern)
{
  const char *p;
  idltype_s e;
  hiter m;

  Tcl_Obj *r = Tcl_NewListObj(0, NULL);
  p =  pattern ? Tcl_GetString(pattern) : NULL;

  for(e = type_first(t, &m); e; e = type_next(&m)) {
    if (p && type_name(e) && !Tcl_StringMatch(type_name(e), p))
      continue;

    Tcl_ListObjAppendElement(
      interp, r, Tcl_NewStringObj(type_genref(e), -1));
  }

  return r;
}
