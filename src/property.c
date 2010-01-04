/*
 * Copyright (c) 2009-2010 LAAS/CNRS
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
 *                                           Anthony Mallet on Tue Dec 29 2009
 */
#include "acgenom.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>

#include "genom.h"


/* --- local data ---------------------------------------------------------- */

struct prop_s {
  tloc loc;
  propkind kind;
  const char *name;

  union {
    idltype_s type;	/**< IDS */
    const char *text;	/**< version, e-mail */
    clist_s clist;	/**< require, build-require */
    cval value;		/**< period, delay, priority, stack */
    codel_s codel;	/**< codel */
    hash_s hash;	/**< throws */
    task_s task;	/**< task */
  };
};

tloc		prop_loc(prop_s p) { assert(p); return p->loc; }
const char *	prop_name(prop_s p) { assert(p); return p->name; }
propkind	prop_kind(prop_s p) { assert(p); return p->kind; }


/* --- prop_create --------------------------------------------------------- */

/** Create a property
 */
static prop_s
prop_new(tloc l, propkind k, const char *name)
{
  prop_s p;
  assert(name);

  p = malloc(sizeof(*p));
  if (!p) {
    warnx("memory exhausted, cannot create property");
    return NULL;
  }

  p->loc = l;
  p->kind = k;
  p->name = string(name);
  p->type = NULL;

  xwarnx("created property %s", p->name);
  return p;
}

prop_s
prop_newids(tloc l, idltype_s t)
{
  assert(t);
  if (type_kind(t) == IDL_CONST) {
    parserror(l, "invalid %s type for ids",
	      type_strkind(type_kind(type_final(t))));
    return NULL;
  }
  switch(type_kind(type_final(t))) {
    case IDL_BOOL: case IDL_USHORT: case IDL_SHORT: case IDL_ULONG:
    case IDL_LONG: case IDL_FLOAT: case IDL_DOUBLE: case IDL_CHAR:
    case IDL_OCTET: case IDL_STRING: case IDL_ENUM: case IDL_ENUMERATOR:
    case IDL_ARRAY: case IDL_SEQUENCE: case IDL_STRUCT: case IDL_UNION:
      break;

    case IDL_ANY: case IDL_FORWARD_STRUCT: case IDL_FORWARD_UNION:
      parserror(l, "invalid %s type for ids",
		type_strkind(type_kind(type_final(t))));
      return NULL;

    case IDL_CONST: case IDL_CASE: case IDL_MEMBER: case IDL_TYPEDEF:
      /* not a valid return from type_final() */
      assert(0); break;
  }

  prop_s p = prop_new(l, PROP_IDS, prop_strkind(PROP_IDS));
  if (!p) return NULL;

  p->type = t;
  return p;
}

prop_s
prop_newstring(tloc l, propkind k, const char *s)
{
  prop_s p = prop_new(l, k, prop_strkind(k));
  if (!p) return NULL;
  assert(s);

  p->text = string(s);
  return p;
}

prop_s
prop_newhash(tloc l, propkind k, hash_s h)
{
  prop_s p = prop_new(l, k, prop_strkind(k));
  if (!p) return NULL;
  assert(h);

  p->hash = h;
  return p;
}

prop_s
prop_newrequire(tloc l, propkind k, clist_s c)
{
  prop_s p = prop_new(l, k, prop_strkind(k));
  if (!p) return NULL;
  assert(c);

  p->clist = c;
  return p;
}

prop_s
prop_newvalue(tloc l, propkind k, cval c)
{
  prop_s p = prop_new(l, k, prop_strkind(k));
  if (!p) return NULL;

  p->value = c;
  return p;
}

prop_s
prop_newcodel(tloc l, codel_s c)
{
  prop_s p = prop_new(l, PROP_CODEL, strings(
			prop_strkind(PROP_CODEL), " ", codel_name(c), NULL));
  if (!p) return NULL;

  p->codel = c;
  return p;
}

prop_s
prop_newtask(tloc l, const char *name)
{
  task_s t;
  prop_s p;

  if (strcmp(name, CNTRL_TASK_NAME)) {
    t = comp_task(comp_dotgen(), name);
    if (!t) {
      parserror(l, "unknown task '%s'", name);
      return NULL;
    }
  } else t = NULL;

  p = prop_new(l, PROP_TASK, prop_strkind(PROP_TASK));
  if (!p) return NULL;
  p->task = t;
  return p;
}


/* --- prop_type ----------------------------------------------------------- */

idltype_s
prop_type(prop_s p)
{
  assert(p);
  assert(
    p->kind == PROP_IDS);
  return p->type;
}


/* --- prop_value ---------------------------------------------------------- */

cval *
prop_value(prop_s p)
{
  assert(p);
  assert(
    p->kind == PROP_PERIOD || p->kind == PROP_DELAY ||
    p->kind == PROP_PRIORITY || p->kind == PROP_STACK);
  return &p->value;
}


/* --- prop_destroy -------------------------------------------------------- */

/** Destroy a property
 */
void
prop_destroy(prop_s p)
{
  if (p) {
    xwarnx("destroyed property %s", p->name);
    free(p);
  }
}


/* --- prop_strkind -------------------------------------------------------- */

/** Return a property kind as a string
 */

const char *
prop_strkind(propkind k)
{
  switch(k) {
    case PROP_DOC:		return "doc";
    case PROP_IDS:		return "ids";
    case PROP_VERSION:		return "version";
    case PROP_LANG:		return "language";
    case PROP_EMAIL:		return "e-mail";
    case PROP_REQUIRE:		return "require";
    case PROP_BUILD_REQUIRE:	return "build-require";
    case PROP_PERIOD:		return "period";
    case PROP_DELAY:		return "delay";
    case PROP_PRIORITY:		return "priority";
    case PROP_STACK:		return "stack";
    case PROP_TASK:		return "task";
    case PROP_CODEL:		return "codel";
    case PROP_THROWS:		return "throws";
    case PROP_INTERRUPTS:	return "interrupts";
    case PROP_BEFORE:		return "before";
    case PROP_AFTER:		return "after";
  }

  assert(0);
  return NULL;
}
