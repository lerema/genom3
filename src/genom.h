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
 *                                           Anthony Mallet on Sat Dec 19 2009
 */
#ifndef H_GENOM
#define H_GENOM

#include <limits.h>

/** runtime options */
extern struct runopt_s {
  char input[PATH_MAX];	/** absolute path name of input file */
  char tmpl[PATH_MAX];	/** name of template file */

  int verbose;		/** be verbose */
  int preproc;		/** preprocess file only */
  char tmpdir[PATH_MAX];/** temporary directory */
  int cppdotgen;	/** cpp accepts .gen file extension */
} runopt;

void	xwarnx(const char *fmt, ...);

int	cpp_optappend(const char *opt, int index);
int	cpp_optrm(int index);
int	cpp_invoke(const char *in, int out);
int	cpp_wait(void);


/* --- parsers ------------------------------------------------------------- */

typedef struct tloc {
  char *file;
  int line, col;
} tloc;

int	dotgenparse(void);
void	parserror(tloc l, const char *fmt, ...);
void	parsenoerror(tloc l, const char *fmt, ...);
void	parsewarning(tloc l, const char *fmt, ...);


/* --- hash tables --------------------------------------------------------- */

typedef struct hash_s *hash_s;
typedef struct hentry_s *hentry_s;
typedef void (*hrelease_f)(void *);
typedef struct hiter {
  hentry_s current;
  const char *key;
  void *value;
} hiter;

hash_s	hash_create(const char *name, int entries);
void	hash_destroy(hash_s h);
int	hash_insert(hash_s h, const char *key, void *value,
		hrelease_f release);

int	hash_remove(hash_s h, const char *key, int release);
void *	hash_find(hash_s h, const char *key);
int	hash_first(hash_s h, hiter *i);
int	hash_after(hash_s h, void *value, hiter *i);
int	hash_next(hiter *i);
void	hash_pstat(hash_s h);


/* --- scopes -------------------------------------------------------------- */

typedef struct scope_s *scope_s;
typedef struct idltype_s *idltype_s;
typedef enum scopekind {
  SCOPE_MODULE,
  SCOPE_STRUCT,
  SCOPE_UNION
} scopekind;

const char *	scope_name(scope_s s);
const char *	scope_fullname(scope_s s);
scope_s		scope_parent(scope_s s);
scope_s		scope_current(void);
scope_s		scope_global(void);

idltype_s	scope_findtype(scope_s s, const char *name);
int		scope_addtype(scope_s s, idltype_s t);
int		scope_deltype(scope_s s, idltype_s t);
int		scope_firstype(scope_s s, hiter *i);
int		scope_nextype(hiter *i);

scope_s		scope_push(tloc l, const char *name, scopekind k);
scope_s		scope_pop(void);
scope_s		scope_detach(scope_s s);
int		scope_pushglobal(void);

void		scope_destroy(scope_s s);


/* --- constants ----------------------------------------------------------- */

typedef enum cvalkind {
  CST_VOID,		/**< no value (used for default case labels) */
  CST_BOOL,		/**< boolean */
  CST_UINT,		/**< unsigned integer */
  CST_INT,		/**< signed integer */
  CST_FLOAT,		/**< floating point */
  CST_CHAR,		/**< character */
  CST_STRING,		/**< string */
  CST_ENUM,		/**< enumerator from enum */
} cvalkind;

typedef struct clist_s *clist_s;
typedef struct cval {
  cvalkind k;
  union {
    unsigned char b;
    unsigned long u;
    signed long i;
    double f;
    char c;
    const char *s;
    idltype_s e;
  };
} cval;
typedef struct citer {
  clist_s current;
  cval *value;
} citer;

int	const_equal(cval a, cval b);
int	const_unaryop(cval *value, char op);
int	const_binaryop(cval *value, char op, cval arg);
int	const_convert(cval *value, cvalkind k);
int	const_cast(tloc l, cval *value, idltype_s t);

clist_s	clist_append(clist_s l, cval v, int unique);
void	clist_destroy(clist_s l);
int	clist_first(clist_s l, citer *i);
int	clist_next(citer *i);


/* --- declarators --------------------------------------------------------- */

typedef struct dcl_s *dcl_s;
typedef struct dcliter {
  dcl_s d;
  unsigned int current;
  unsigned int value;
} dcliter;

const char *	dcl_name(dcl_s d);
idltype_s	dcl_type(dcl_s d);
int		dcl_isarray(dcl_s d);

dcl_s		dcl_create(tloc l, const char *name);
dcl_s		dcl_adddim(dcl_s dcl, unsigned long dim);
idltype_s	dcl_settype(dcl_s dcl, idltype_s t);
void		dcl_destroy(dcl_s d);

int		dcl_inner(dcl_s d, dcliter *i);
int		dcl_next(dcliter *i);


/* --- IDL types ----------------------------------------------------------- */

typedef enum idlkind {
  IDL_BOOL,		/**< boolean */
  IDL_USHORT,		/**< unsigned short */
  IDL_SHORT,		/**< short */
  IDL_ULONG,		/**< unsigned long */
  IDL_LONG,		/**< long */
  IDL_FLOAT,		/**< float */
  IDL_DOUBLE,		/**< double */
  IDL_CHAR,		/**< char */
  IDL_OCTET,		/**< octet */
  IDL_STRING,		/**< string */
  IDL_ANY,		/**< any */

  IDL_CONST,		/**< constant */
  IDL_ENUM,		/**< enumerated type */
  IDL_ENUMERATOR,	/**< constant in an enumerated type */
  IDL_ARRAY,		/**< array */
  IDL_SEQUENCE,		/**< sequence */
  IDL_STRUCT,		/**< struct */
  IDL_MEMBER,		/**< element of struct */
  IDL_UNION,		/**< union */
  IDL_CASE,		/**< element of union */

  IDL_TYPEDEF,		/**< typedef */

  IDL_FORWARD_STRUCT,	/**< forward struct declaration */
  IDL_FORWARD_UNION	/**< forward union declaration */
} idlkind;

tloc		type_loc(idltype_s t);
const char *	type_name(idltype_s t);
const char *	type_fullname(idltype_s t);
idlkind		type_kind(idltype_s t);
cval		type_constvalue(idltype_s t);
idltype_s	type_enumeratorenum(idltype_s t);
idltype_s	type_elemtype(idltype_s t, unsigned int *len);
void		type_setscope(idltype_s t, scope_s s);

idltype_s	type_newbasic(tloc l, const char *name, idlkind k);
idltype_s	type_newforward(tloc l, const char *name, idlkind k);
idltype_s	type_newstring(tloc l, const char *name, unsigned long len);
idltype_s	type_newsequence(tloc l, const char *name, idltype_s t,
			unsigned long len);
idltype_s	type_newconst(tloc l, const char *name, idltype_s t, cval v);
idltype_s	type_newenum(tloc l, const char *name, hash_s enumerators);
idltype_s	type_newenumerator(tloc l, const char *name);
idltype_s	type_newarray(tloc l, const char *name, idltype_s t,
			unsigned long len);
idltype_s	type_newstruct(tloc l, const char *name, scope_s s);
idltype_s	type_newmember(tloc l, const char *name, idltype_s t);
idltype_s	type_newunion(tloc l, const char *name, idltype_s t, scope_s s);
idltype_s	type_newcase(tloc l, const char *name, idltype_s t, clist_s c);
idltype_s	type_newalias(tloc l, const char *name, idltype_s t);
void		type_destroy(idltype_s t);

int		type_equal(idltype_s a, idltype_s b);
idltype_s	type_find(const char *name);
idltype_s	type_member(idltype_s t, const char *name);
idltype_s	type_final(idltype_s t);
idltype_s	type_first(idltype_s t, hiter *i);
idltype_s	type_after(idltype_s t, idltype_s p, hiter *i);
idltype_s	type_next(hiter *i);

const char *	type_strkind(idlkind k);

void		type_usage(void);


/* --- GenoM object properties --------------------------------------------- */

#define CNTRL_TASK_NAME		"control"
#define ALL_SERVICE_NAME	"all"

typedef struct codel_s *codel_s;

typedef struct prop_s *prop_s;
typedef enum propkind {
  PROP_DOC,		/**< doc string */
  PROP_IDS,		/**< internal data structure */
  PROP_VERSION,		/**< component version */
  PROP_LANG,		/**< codels language */
  PROP_EMAIL,		/**< support e-mail */

  PROP_REQUIRE,		/**< run-time requirements */
  PROP_BUILD_REQUIRE,	/**< build requirements */

  PROP_PERIOD,		/**< period */
  PROP_DELAY,		/**< delay */
  PROP_PRIORITY,	/**< priority */
  PROP_STACK,		/**< stack size */

  PROP_TASK,		/**< service task */
  PROP_CODEL,		/**< codels */
  PROP_THROWS,		/**< errors from codels */
  PROP_INTERRUPTS,	/**< interrupted services */
  PROP_BEFORE,		/**< services requirements */
  PROP_AFTER		/**< services requirements */
} propkind;

tloc		prop_loc(prop_s p);
const char *	prop_name(prop_s p);
propkind	prop_kind(prop_s p);

prop_s		prop_newids(tloc l, idltype_s t);
prop_s		prop_newstring(tloc l, propkind k, const char *s);
prop_s		prop_newhash(tloc l, propkind k, hash_s h);
prop_s		prop_newrequire(tloc l, propkind k, clist_s c);
prop_s		prop_newvalue(tloc l, propkind k, cval c);
prop_s		prop_newcodel(tloc l, codel_s c);
prop_s		prop_newtask(tloc l, const char *name);
void		prop_destroy(prop_s p);

idltype_s	prop_type(prop_s p);
cval *		prop_value(prop_s p);

const char *	prop_strkind(propkind k);


/* --- component ----------------------------------------------------------- */

typedef struct comp_s *comp_s;
typedef struct task_s *task_s;
typedef struct port_s *port_s;
typedef struct service_s *service_s;
typedef enum portkind {
  PORT_IN,
  PORT_OUT,
  PORT_EVENT
} portkind;

const char *	comp_name(comp_s c);
idltype_s	comp_ids(comp_s c);
port_s		comp_port(comp_s c, const char *name);
task_s		comp_task(comp_s c, const char *name);
comp_s		comp_dotgen(void);
const char *	task_name(task_s c);
tloc		port_loc(port_s p);
const char *	port_name(port_s p);
portkind	port_kind(port_s p);
idltype_s	port_type(port_s p);

comp_s		comp_create(tloc l, const char *name, hash_s props);
task_s		comp_addtask(tloc l, const char *name, hash_s props);
port_s		comp_addport(tloc l, portkind k, const char *name,
			idltype_s t);
service_s	comp_addservice(tloc l, const char *name, hash_s params,
			hash_s props);

void		task_destroy(task_s t);
void		port_destroy(port_s p);
void		service_destroy(service_s s);


/* --- codel --------------------------------------------------------------- */

typedef struct param_s *param_s;
typedef struct initer_s *initer_s;
typedef enum pdir {
  P_IN,
  P_OUT,
  P_INOUT,

  P_INPORT,
  P_OUTPORT
} pdir;

const char *	codel_name(codel_s c);
hash_s		codel_triggers(codel_s c);
const char *	param_name(param_s p);

codel_s		codel_create(tloc l, const char *name, hash_s triggers,
			hash_s yields, hash_s params);

param_s		param_newids(tloc l, pdir d, const char *name);
param_s		param_newport(tloc l, pdir d, const char *name, port_s port);
void		param_destroy(param_s p);

int		param_setname(tloc l, param_s p, const char *name);
int		param_setmember(tloc l, param_s p, const char *name);
int		param_setelement(tloc l, param_s p, unsigned int e);
int		param_setinitv(tloc l, param_s p, initer_s i);

const char *	param_strdir(pdir d);

initer_s	initer_create(unsigned int a, const char *m, initer_s s,
			cval v);
int		initer_setdoc(initer_s i, const char *d);
initer_s	initer_append(initer_s l, initer_s m);
void		initer_destroy(initer_s l);


/* --- strings ------------------------------------------------------------- */

char *	string(const char *s);
char *	strings(const char *src, ...);
void	string_usage(void);


/* --- compat -------------------------------------------------------------- */

#ifndef HAVE_STRLCPY
size_t	strlcpy(char *dst, const char *src, size_t siz);
#endif

#ifndef HAVE_STRLCAT
size_t	strlcat(char *dst, const char *src, size_t siz);
#endif

#endif /* H_GENOM */
