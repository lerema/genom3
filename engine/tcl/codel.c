/*
 * Copyright (c) 2011-2013,2015,2020,2022 LAAS/CNRS
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
 *                                           Anthony Mallet on Wed Mar  9 2011
 */
#include "acgenom.h"

#include <assert.h>

#include <tcl.h>

#include "genom.h"
#include "engine.h"


/* --- local data ---------------------------------------------------------- */

static Tcl_Obj *	param_list(Tcl_Interp *interp, codel_s c, int objc,
				Tcl_Obj *const dfilter[]);


/* --- codel command ------------------------------------------------------- */

/*/
 * == *$codel* TCL engine command
 *
 * Those commands manipulate codels objects and return information about
 * them. They all take a codels object as their first argument, noted `$codel`
 * in the following command descriptions. Such an object is typically returned
 * by other procedures.
 */

/** Implements the command associated to a codel object.
 */
int
codel_cmd(ClientData v, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
  enum codelidx {
    codelidx_name, codelidx_kind, codelidx_params, codelidx_yields,
    codelidx_triggers, codelidx_task, codelidx_service, codelidx_mutex,
    codelidx_cname, codelidx_signature, codelidx_invoke, codelidx_loc,
    codelidx_class
  };
  static const char *args[] = {
    [codelidx_name] = "name", [codelidx_kind] = "kind",
    [codelidx_params] = "parameters", [codelidx_yields] = "yields",
    [codelidx_triggers] = "triggers", [codelidx_task] = "task",
    [codelidx_service] = "service", [codelidx_mutex] = "mutex",
    [codelidx_cname] = "cname", [codelidx_signature] = "signature",
    [codelidx_invoke] = "invoke", [codelidx_loc] = "loc",
    [codelidx_class] = "class", NULL
  };
  codel_s c = v;
  Tcl_Obj *r = NULL;
  int s;

  int i = codelidx_name; /* return name by default */

  if (objc > 1) {
    s = Tcl_GetIndexFromObj(interp, objv[1], args, "subcommand", 0, &i);
    if (s != TCL_OK) return s;
  }
  if (i == codelidx_params) {
    /* any number of direction filter arguments */;
  } else if (i == codelidx_signature) {
    if (objc > 4) {
      Tcl_WrongNumArgs(interp, 2, objv, "?separator? ?location?");
      return TCL_ERROR;
    }
  } else if (i == codelidx_invoke) {
    if (objc != 3) {
      Tcl_WrongNumArgs(interp, 2, objv, "params");
      return TCL_ERROR;
    }
  } else if (i == codelidx_loc) {
    if (objc > 3) {
      Tcl_WrongNumArgs(interp, 0, objv, "$codel loc ?element?");
      return TCL_ERROR;
    }
  } else {
    if (objc > 2) {
      Tcl_WrongNumArgs(interp, 0, objv, "$codel subcommand");
      return TCL_ERROR;
    }
  }
  switch((enum codelidx)i) {
    /*/
     * [[name]]
     * === *$codel name*
     *
     * Return the name of the codel.
     */
    case codelidx_name:
      r = Tcl_NewStringObj(codel_name(c), -1);
      break;

    /*/
     * [[kind]]
     * === *$codel kind*
     *
     * Return the codel kind, among `sync` or `async`.
     */
    case codelidx_kind:
      r = Tcl_NewStringObj(codel_strkind(codel_kind(c)), -1);
      break;

    /*/
     * [[params]]
     * === *$codel parameters*
     *
     * Return the list of codel parameters.
     */
    case codelidx_params:
      r = param_list(interp, c, objc>2?objc-2:0, objv+2);
      if (!r) return TCL_ERROR;
      break;

    /*/
     * [[yields]]
     * === *$codel yields*
     *
     * Return the list of link:cmd-type{outfilesuffix}[`events`] that this
     * codel can yield to after execution.
     */
    case codelidx_yields: {
      hiter i;

      r = Tcl_NewListObj(0, NULL);
      for(hash_first(codel_yields(c), &i); i.current; hash_next(&i)) {
	Tcl_ListObjAppendElement(
	  interp, r, Tcl_NewStringObj(type_genref(i.value), -1));
      }
      break;
    }

    /*/
     * [[triggers]]
     * === *$codel triggers*
     *
     * Return the list of link:cmd-type{outfilesuffix}[`events`] that trigger
     * the execution of this codel.
     */
    case codelidx_triggers: {
      hiter i;

      r = Tcl_NewListObj(0, NULL);
      for(hash_first(codel_triggers(c), &i); i.current; hash_next(&i)) {
	Tcl_ListObjAppendElement(
	  interp, r, Tcl_NewStringObj(type_genref(i.value), -1));
      }
      break;
    }

    /*/
     * [[task]]
     * === *$codel task*
     *
     * Return the task of a codel for codels defined in a task, or an error if
     * the codel belongs to a service.
     */
    case codelidx_task:
      if (*codel_task(c))
	r = Tcl_NewStringObj(task_genref(*codel_task(c)), -1);
      break;

    /*/
     * [[service]]
     * === *$codel service*
     *
     * Return the service of a codel for codels defined in a service, or an
     * error if the codel belongs to a task.
     */
    case codelidx_service:
      if (*codel_service(c))
	r = Tcl_NewStringObj(service_genref(*codel_service(c)), -1);
      break;

    /*/
     * [[mutex]]
     * === *$codel mutex*
     *
     * Return a list of link:cmd-codel{outfilesuffix}[`codels`] and
     * link:cmd-service{outfilesuffix}[`services`] that may access internal
     * resources used by the codel. All these codels cannot run simultaneously
     * and are mutually exclusive.
     */
    case codelidx_mutex: {
      hiter i;
      hash_s h = codel_codel_mutex(c);
      if (!h) {
        Tcl_AppendResult(interp, "internal error", NULL);
        return TCL_ERROR;
      }

      r = Tcl_NewListObj(0, NULL);
      for(hash_first(h, &i); i.current; hash_next(&i)) {
        Tcl_ListObjAppendElement(
          interp, r, Tcl_NewStringObj(codel_genref(i.value), -1));
      }
      hash_destroy(h, 1);

      h = codel_service_mutex(c);
      if (!h) {
        Tcl_AppendResult(interp, "internal error", NULL);
        return TCL_ERROR;
      }

      for(hash_first(h, &i); i.current; hash_next(&i)) {
        Tcl_ListObjAppendElement(
          interp, r, Tcl_NewStringObj(service_genref(i.value), -1));
      }
      hash_destroy(h, 1);
      break;
    }

    /*/
     * [[cname]]
     * === *$codel cname*
     * Return the cannonical name of a codel for the current
     * link:cmd-language{outfilesuffix}#lang[`language`].
     */
    case codelidx_cname:
    /*/
     * [[signature]]
     * === *$codel signature*
     * Return the signature of a codel for the current
     * link:cmd-language{outfilesuffix}#lang[`language`].
     */
    case codelidx_signature:
    /*/
     * [[invoke]]
     * === *$codel invoke 'params'*
     * Return a string corresponding to the invocation of a codel in the current
     * link:cmd-language{outfilesuffix}#lang[`language`]. See
     * link:cmd-language{outfilesuffix}#invoke[`language invoke`].
     */
    case codelidx_invoke: {
      Tcl_Obj *argv[] = {
        Tcl_NewStringObj("language::", -1),
        objv[0],
        objc>2?objv[2]:NULL,
        objc>3?objv[3]:NULL
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
     * [[loc]]
     * === *$codel loc* [file|line|column|context]
     *
     * Return a list describing the source location where that codel is
     * defined. The list contains four elements: the file name, the line
     * number, the column number and the original component context of the
     * definition. If an optional argument is given, only the corresponding
     * element is returned.
     */
    case codelidx_loc:
      r = tloc_item(interp, objc > 2 ? objv[2]:NULL, codel_loc(c));
      if (!r) return TCL_ERROR;
      break;

    /*/
     * [[class]]
     * === *$codel class*
     * Return the string `codel`.
     */
    case codelidx_class:
      r = Tcl_NewStringObj("codel", -1);
      break;
  }

  if (!r) {
    Tcl_AppendResult(interp, "undefined member \"", args[i], "\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, r);
  return TCL_OK;
}



/* --- param_list ---------------------------------------------------------- */

/** return a Tcl list of ports
 */
static Tcl_Obj *
param_list(Tcl_Interp *interp, codel_s c, int objc, Tcl_Obj *const dfilter[])
{
  enum pdiridx {
    pdiridx_in, pdiridx_out, pdiridx_inout,
    pdiridx_ids, pdiridx_local, pdiridx_port, pdiridx_remote
  };
  static const char *dirarg[] = {
    [pdiridx_in] = "in", [pdiridx_out] = "out",
    [pdiridx_inout] = "inout", [pdiridx_ids] = "ids",
    [pdiridx_local] = "local", [pdiridx_port] = "port",
    [pdiridx_remote] = "remote", NULL
  };
  int e, f, d = -1, sc;
  hiter i;
  Tcl_Obj *r = Tcl_NewListObj(0, NULL);

  /* build filtered list of parameters */
  for(hash_first(codel_params(c), &i); i.current; hash_next(&i)) {

    /* iterate over optional direction filters */
    f = (objc == 0);
    for(sc = 0; !f && sc < objc; sc++) {
      e = Tcl_GetIndexFromObj(interp, dfilter[sc], dirarg, "direction", 0, &d);
      if (e != TCL_OK) return NULL;

      switch(d) {
        case pdiridx_in:
          if (param_dir(i.value) == P_IN) f = 1;
          break;
        case pdiridx_out:
          if (param_dir(i.value) == P_OUT) f = 1;
          break;
        case pdiridx_inout:
          if (param_dir(i.value) == P_INOUT) f = 1;
          break;

        case pdiridx_ids:
          if (param_src(i.value) == P_IDS) f = 1;
          break;
        case pdiridx_local:
          if (param_src(i.value) == P_LOCAL) f = 1;
          break;
        case pdiridx_port:
          if (param_src(i.value) == P_PORT) f = 1;
          break;
        case pdiridx_remote:
          if (param_src(i.value) == P_REMOTE) f = 1;
          break;
      }
    }
    if (f)
      Tcl_ListObjAppendElement(
        interp, r, Tcl_NewStringObj(param_genref(i.value), -1));
  }

  return r;
}
