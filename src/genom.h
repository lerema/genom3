/*
 * Copyright (c) 2009-2015,2017,2022-2023 LAAS/CNRS
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

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

/** helpers */
#ifdef  __GNUC__
# pragma GCC diagnostic error "-Wswitch-enum"
#endif

#define nodefault	default: assert(!"unreachable case"); abort()


/** runtime options */
extern struct runopt_s {
  char tmpl[PATH_MAX];	/** name of template file */

  int verbose;		/** be verbose */
  int debug;		/** activate some debugging options */
  int preproc;		/** preprocess file only */
  int parse;		/** parse file only */
  int list;		/** list available templates */
  char engine[PATH_MAX];/** generator engine */
  char *sitetmplpath;	/** site templates directories, colon separated */
  char sysdir[PATH_MAX];/** system files directory */
  char tmpldir[PATH_MAX];/** genom template directory */
  char tmpdir[PATH_MAX];/** temporary directory */
  char cpppath[PATH_MAX];/** genom cpp preprocessor */
  char dgpath[PATH_MAX];/** input file path */

  const char *genom;	/** Executable path */
  const char *cmdline;	/** Relevant options to genom to register */
  const char *notice;	/** special comment put verbatim in generated files */
} runopt;

void	xwarnx(const char *fmt, ...);
void	xwarnx_verbosity(int verbose);
void	xmsg(const char *pfix, const char *fmt, ...);

int	cpp_optappend(const char *opt, int index);
int	cpp_optrm(int index);
int	cpp_invoke(char *in[], int out);
char *	cpp_getnotice(const char *in);
int	cpp_wait(void);


/* --- parsers ------------------------------------------------------------- */

typedef struct hash_s *hash_s;
typedef struct comp_s *comp_s;

typedef struct tloc {
  char *file;
  int line, col;
  comp_s context;
} tloc;

typedef enum dotgen_input_kind {
  DG_INPUT_FILE,
  DG_INPUT_BUFFER
} dotgen_input_kind;

extern int nerrors;
extern int nwarnings;

void	dotgen_input(dotgen_input_kind k, ...);
int	dotgenparse(void);
int	dotgen_consolidate(void);
hash_s	dotgen_hdeps(void);
hash_s	dotgen_hrequire(void);
hash_s	dotgen_hprovide(void);
hash_s	dotgen_hmasquerade(void);

void	parserror(tloc l, const char *fmt, ...);
void	parsenoerror(tloc l, const char *fmt, ...);
void	parsewarning(tloc l, const char *fmt, ...);


/* --- hash tables --------------------------------------------------------- */

typedef struct hentry_s *hentry_s;
typedef void (*hrelease_f)(void *);
typedef struct hiter {
  hentry_s current;
  const char *key;
  void *value;
} hiter;

hash_s	hash_create(const char *name, int entries);
void	hash_destroy(hash_s h, int release);
int	hash_insert(hash_s h, const char *key, void *value,
		hrelease_f release);
int	hash_set(hash_s h, const char *key, void *value);
int	hash_rename(hash_s h, const char *key, const char *new);

int	hash_remove(hash_s h, const char *key, int release);
void *	hash_find(hash_s h, const char *key);
int	hash_first(hash_s h, hiter *i);
int	hash_after(hash_s h, void *value, hiter *i);
int	hash_next(hiter *i);
void	hash_pstat(hash_s h);


/* --- scopes -------------------------------------------------------------- */

#define GENOM_NAMESPACE		"genom"

typedef struct scope_s *scope_s;
typedef struct idltype_s *idltype_s;
typedef enum scopekind {
  SCOPE_MODULE,
  SCOPE_STRUCT,
  SCOPE_UNION,
  SCOPE_EXCEPTION
} scopekind;

scopekind	scope_kind(scope_s s);
const char *	scope_name(scope_s s);
const char *	scope_fullname(scope_s s);
hash_s		scope_types(scope_s s);
scope_s		scope_parent(scope_s s);
scope_s		scope_current(void);
scope_s		scope_global(void);
scope_s		scope_set(scope_s s);

idltype_s	scope_findtype(scope_s s, const char *name);
int		scope_addtype(scope_s s, idltype_s t);
int		scope_deltype(scope_s s, idltype_s t);
int		scope_renametype(scope_s s, idltype_s t, const char *new);
idltype_s	scope_firstype(scope_s s, hiter *i);
idltype_s	scope_nextype(hiter *i);

scope_s		scope_push(tloc l, const char *name, scopekind k);
scope_s		scope_pop(void);
scope_s		scope_detach(scope_s s);
int		scope_pushglobal(void);

void		scope_destroy(scope_s s);

const char *	scope_strkind(scopekind k);


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
    uint64_t u;
    int64_t i;
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

const char *	const_strkind(cvalkind k);
const char *	const_strval(cval v);

clist_s	clist_append(clist_s l, cval v, int unique);
clist_s	clist_prepend(clist_s l, cval v, int unique);
cval	clist_pop(clist_s *l);
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
dcl_s		dcl_adddim(dcl_s dcl, uint32_t dim);
idltype_s	dcl_settype(dcl_s dcl, idltype_s t);
void		dcl_destroy(dcl_s d);

int		dcl_inner(dcl_s d, dcliter *i);
int		dcl_next(dcliter *i);


/* --- IDL types ----------------------------------------------------------- */

typedef struct port_s *port_s;
typedef struct remote_s *remote_s;

typedef enum idlkind {
  IDL_BOOL,		/**< boolean */
  IDL_USHORT,		/**< unsigned short */
  IDL_SHORT,		/**< short */
  IDL_ULONG,		/**< unsigned long */
  IDL_LONG,		/**< long */
  IDL_ULONGLONG,	/**< unsigned long long */
  IDL_LONGLONG,		/**< long long */
  IDL_FLOAT,		/**< float */
  IDL_DOUBLE,		/**< double */
  IDL_CHAR,		/**< char */
  IDL_OCTET,		/**< octet */
  IDL_STRING,		/**< string */
  IDL_ANY,		/**< any */
  IDL_NATIVE,		/**< native object */
  IDL_EXCEPTION,	/**< exception */

  IDL_CONST,		/**< constant */
  IDL_ENUM,		/**< enumerated type */
  IDL_ENUMERATOR,	/**< constant in an enumerated type */
  IDL_ARRAY,		/**< array */
  IDL_SEQUENCE,		/**< sequence */
  IDL_OPTIONAL,		/**< optional */
  IDL_STRUCT,		/**< struct */
  IDL_MEMBER,		/**< element of struct */
  IDL_UNION,		/**< union */
  IDL_CASE,		/**< element of union */

  IDL_TYPEDEF,		/**< typedef */

  IDL_FORWARD_STRUCT,	/**< forward struct declaration */
  IDL_FORWARD_UNION,	/**< forward union declaration */

  IDL_EVENT,		/**< event */
  IDL_PAUSE_EVENT,	/**< pause event */
  IDL_PORT,		/**< port object */
  IDL_REMOTE		/**< rpc object */
} idlkind;

hash_s		type_all(void);

tloc		type_loc(idltype_s t);
const char *	type_name(idltype_s t);
const char *	type_fullname(idltype_s t);
idlkind		type_kind(idltype_s t);
scope_s		type_scope(idltype_s t);
cval		type_constvalue(idltype_s t);
idltype_s	type_type(idltype_s t);
uint32_t	type_length(idltype_s t);
idltype_s	type_discriminator(idltype_s t);
clist_s		type_casevalues(idltype_s t);
hash_s		type_members(idltype_s t);
scope_s		type_membersscope(idltype_s t);
port_s		type_port(idltype_s t);
remote_s	type_remote(idltype_s t);

idltype_s	type_newbasic(tloc l, const char *name, idlkind k);
idltype_s	type_newforward(tloc l, const char *name, idlkind k);
idltype_s	type_newstring(tloc l, const char *name, uint32_t len);
idltype_s	type_newsequence(tloc l, const char *name, idltype_s t,
			uint32_t len);
idltype_s	type_newoptional(tloc l, const char *name, idltype_s t);
idltype_s	type_newconst(tloc l, const char *name, idltype_s t, cval v);
idltype_s	type_newenum(tloc l, const char *name, hash_s enumerators);
idltype_s	type_newenumerator(tloc l, const char *name);
idltype_s	type_newarray(tloc l, const char *name, idltype_s t,
			uint32_t len);
idltype_s	type_newstruct(tloc l, const char *name, scope_s s);
idltype_s	type_newmember(tloc l, const char *name, idltype_s t);
idltype_s	type_newunion(tloc l, const char *name, idltype_s t, scope_s s);
idltype_s	type_newcase(tloc l, const char *name, idltype_s t, clist_s c);
idltype_s	type_newalias(tloc l, const char *name, idltype_s t);
idltype_s	type_newexception(tloc l, const char *name, scope_s s);
idltype_s	type_newport(tloc l, const char *name, port_s p);
idltype_s	type_newremote(tloc l, const char *name, remote_s r);
int		type_renew(idltype_s t);
void		type_destroy(idltype_s t);

int		type_fixed(idltype_s t);
int		type_native(idltype_s t, int verbose);
int		type_equal(idltype_s a, idltype_s b);
idltype_s	type_find(const char *name);
idltype_s	type_member(idltype_s t, const char *name);
idltype_s	type_final(idltype_s t);
idltype_s	type_parent(idltype_s t);
idltype_s	type_first(idltype_s t, hiter *i);
idltype_s	type_after(idltype_s t, idltype_s p, hiter *i);
idltype_s	type_next(hiter *i);

const char *	type_strkind(idlkind k);

void		type_usage(void);


/* --- GenoM object properties --------------------------------------------- */

#define ALL_SERVICE_NAME		"all"

typedef struct task_s *task_s;
typedef struct codel_s *codel_s;

typedef struct prop_s *prop_s;
typedef enum propkind {
  PROP_DOC,		/**< doc string */
  PROP_IDS,		/**< internal data structure */
  PROP_VERSION,		/**< component version */
  PROP_LANG,		/**< codels language */
  PROP_EMAIL,		/**< support e-mail */

  PROP_REQUIRE,		/**< run-time requirements */
  PROP_CODELS_REQUIRE,	/**< codels requirements */

  PROP_EXTENDS,		/**< interface inheritance */
  PROP_PROVIDES,	/**< interface implementation */
  PROP_USES,		/**< interface use */

  PROP_CLOCKRATE,	/**< clock rate */
  PROP_PERIOD,		/**< period */
  PROP_DELAY,		/**< delay */
  PROP_PRIORITY,	/**< priority */
  PROP_SCHEDULING,	/**< scheduling */
  PROP_STACK,		/**< stack size */

  PROP_TASK,		/**< service task */
  PROP_VALIDATE,	/**< validation codels */
  PROP_SIMPLE_CODEL,	/**< bare codels */
  PROP_FSM_CODEL,	/**< codels in a FSM */
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
prop_s		prop_newcodel(tloc l, propkind k, codel_s c);
prop_s		prop_newtask(tloc l, const char *name);
void		prop_destroy(prop_s p);

idltype_s	prop_type(prop_s p);
const char *	prop_text(prop_s p);
clist_s		prop_list(prop_s p);
idltype_s	prop_value(prop_s p);
task_s		prop_task(prop_s p);
codel_s		prop_codel(prop_s p);
hash_s		prop_hash(prop_s p);

int		prop_merge_list(hash_s p, hash_s m, int ignore_dup);
int		prop_merge(hash_s p, prop_s i, int ignore_dup);

const char *	prop_strkind(propkind k);


/* --- component ----------------------------------------------------------- */

#define COMPONENT_STD_EVENTS { "ether", "start", "stop" }
#define COMPONENT_PAUSE_EVENT_NS "pause"

#define COMPONENT_PROP_DEFAULTS {               \
    { PROP_LANG,	"c" },                  \
    { PROP_VERSION,	"0" },                  \
}

typedef enum compkind {
  COMP_REGULAR,		/* regular component */
  COMP_IFACE,		/* interface */
} compkind;

typedef enum svckind {
  S_ATTRIBUTE,
  S_FUNCTION,
  S_ACTIVITY
} svckind;

typedef struct service_s *service_s;
typedef struct param_s *param_s;

comp_s		comp_active(void);
comp_s		comp_first(void);
comp_s		comp_next(comp_s c);
comp_s		comp_find(const char *name);

tloc		comp_loc(comp_s c);
compkind	comp_kind(comp_s c);
const char *	comp_name(comp_s c);
scope_s		comp_scope(comp_s c);
scope_s		comp_idsscope(comp_s c);
idltype_s	comp_ids(comp_s c);
hash_s		comp_props(comp_s c);
hash_s		comp_tasks(comp_s c);
hash_s		comp_ports(comp_s c);
hash_s		comp_services(comp_s c);
hash_s		comp_remotes(comp_s c);
port_s		comp_port(comp_s c, const char *name);
task_s		comp_task(comp_s c, const char *name);
service_s	comp_service(comp_s c, const char *name);
remote_s	comp_remote(comp_s c, const char *name);
const char *	comp_strkind(compkind k);

comp_s		comp_push(tloc l, const char *name, compkind kind);
comp_s		comp_pop(void);
int		comp_addprop(tloc l, prop_s p);
idltype_s	comp_addids(tloc l, scope_s s);
idltype_s	comp_addevent(tloc l, idlkind k, const char *name);

int		comp_dumpall(FILE *out);
int		comp_dump(comp_s c, FILE *out);

tloc		task_loc(task_s t);
const char *	task_name(task_s t);
comp_s		task_comp(task_s t);
hash_s		task_props(task_s t);
hash_s		task_fsm(task_s t);

task_s		task_create(tloc l, const char *name, hash_s props);
int		task_check(task_s task);
task_s		task_clone(task_s task);
void		task_destroy(task_s t);

tloc		service_loc(service_s s);
const char *	service_name(service_s s);
svckind		service_kind(service_s s);
comp_s		service_comp(service_s s);
hash_s		service_props(service_s s);
hash_s		service_params(service_s s);
hash_s		service_fsm(service_s s);
const char *	service_strkind(svckind k);

service_s	service_create(tloc l, svckind kind, const char *name,
                        hash_s params, hash_s props);
hash_s		service_codel_mutex(service_s service);
int		service_check(service_s service);
service_s	service_clone(service_s service);
void		service_destroy(service_s s);

tloc		remote_loc(remote_s r);
const char *	remote_name(remote_s r);
comp_s		remote_comp(remote_s r);
idltype_s	remote_type(remote_s r);
hash_s		remote_params(remote_s r);
service_s	remote_service(remote_s r);

remote_s	remote_create(tloc l, service_s service);
remote_s	remote_clone(remote_s remote);
void		remote_destroy(remote_s r);


/* --- port ---------------------------------------------------------------- */

typedef enum portdir {
  PORT_IN,
  PORT_OUT
} portdir;

typedef enum portkind {
  PORT_SIMPLE,
  PORT_MULTIPLE
} portkind;

port_s		port_create(tloc l, portdir d, portkind k, const char *name,
                        idltype_s dtype, hash_s props);
port_s		port_clone(port_s port);
port_s		port_use(port_s port);
void		port_destroy(port_s p);

tloc		port_loc(port_s p);
const char *	port_name(port_s p);
portdir		port_dir(port_s p);
portkind	port_kind(port_s p);
comp_s		port_comp(port_s p);
idltype_s	port_type(port_s p);
idltype_s	port_datatype(port_s p);
hash_s		port_props(port_s p);
const char *	port_strdir(portdir d);
const char *	port_strkind(portkind k);


/* --- codel --------------------------------------------------------------- */

typedef struct initer_s *initer_s;

typedef enum psrc {
  P_NOSRC,

  P_IDS,
  P_LOCAL,
  P_PORT,
  P_REMOTE
} psrc;

typedef enum pdir {
  P_NODIR,

  P_IN,
  P_OUT,
  P_INOUT,
} pdir;

typedef enum codelkind {
  CODEL_SYNC,
  CODEL_ASYNC
} codelkind;

tloc		codel_loc(codel_s c);
const char *	codel_name(codel_s c);
const char *	codel_fullname(codel_s c);
codelkind	codel_kind(codel_s c);
hash_s		codel_params(codel_s c);
hash_s		codel_triggers(codel_s c);
hash_s		codel_yields(codel_s c);
task_s *	codel_task(codel_s c);
service_s *	codel_service(codel_s c);
void		codel_setkind(codel_s c, codelkind k);

hash_s		param_locals(void);
void		param_setlocals(hash_s h);
tloc		param_loc(param_s p);
const char *	param_name(param_s p);
psrc		param_src(param_s p);
pdir		param_dir(param_s p);
clist_s		param_member(param_s p);
idltype_s	param_base(param_s p);
idltype_s	param_type(param_s p);
port_s		param_port(param_s p);
remote_s	param_remote(param_s p);
param_s		param_param(param_s p);
initer_s	param_initer(param_s p);

tloc		initer_loc(initer_s i);
unsigned int	initer_index(initer_s i);
const char *	initer_member(initer_s i);
const char *	initer_doc(initer_s i);
cval		initer_value(initer_s i);
initer_s	initer_compound(initer_s i);
initer_s	initer_next(initer_s i);

codel_s		codel_create(tloc l, const char *name, codelkind kind,
			hash_s triggers, hash_s yields, hash_s params);
codel_s		codel_clone(codel_s codel);
hash_s		codel_codel_mutex(codel_s codel);
hash_s		codel_service_mutex(codel_s codel);
hash_s		codel_fsmcreate(tloc l, comp_s comp, hash_s props);
const char *	codel_strkind(codelkind k);
int		codel_check(codel_s codel);

param_s		param_newids(tloc l, pdir dir, const char *name,
			clist_s member, initer_s initer);
param_s		param_newlocal(tloc l, pdir dir, const char *name,
			clist_s member, idltype_s type, initer_s initer);
param_s		param_newport(tloc l, pdir dir, const char *name,
			clist_s member);
param_s		param_newremote(tloc l, pdir dir, const char *name,
			clist_s member);
param_s		param_newcodel(tloc l, psrc src, pdir dir, const char *name,
			clist_s member);
param_s		param_clone(param_s param);
void		param_destroy(param_s p);
int		param_setname(param_s p, const char *name);
int		param_setdir(param_s p, pdir dir);
int		param_setiniter(param_s p, initer_s initer);
initer_s	param_typeiniter(param_s p, idltype_s t);

int		param_equal(param_s p, param_s q);
int		param_list_equal(hash_s l, hash_s m);
int		param_mutex(param_s p, param_s q, int invq);
int		param_list_mutex(hash_s l, hash_s m, int invm);
const char *	param_strsrc(psrc s);
const char *	param_strdir(pdir d);

initer_s	initer_create(tloc l, unsigned int index, const char *member,
			initer_s sub, cval v);
int		initer_setdoc(initer_s i, const char *d);
initer_s	initer_append(initer_s l, initer_s m);
int		initer_matchtype(idltype_s t, initer_s i);
initer_s	initer_typeiniter(initer_s i, idltype_s haystack,
			idltype_s needle);

void		initer_destroy(initer_s l);


/* --- engine -------------------------------------------------------------- */

#define TMPL_SPECIAL_FILE		"template."

typedef struct engdescr {
  const char *name;
  int (*invoke)(const char *tmpl, int argc, char **argv);
} engdescr;

const char *	eng_findtmpl(const char *tmpl);
int		eng_listtmpl(char ***list);
int		eng_seteng(const char *tmpl);
int		eng_optappend(const char *opt, int index);
int		eng_optrm(int index);

int		eng_invoke(void);


/* --- strings ------------------------------------------------------------- */

char *	string(const char *s);
char *	strings(const char *src, ...);
void	bufcat(char **buf, const char *fmt, ...);
void	string_usage(void);

int	opt_append(char ***odb, int *nodb, const char *opt, int index);
int	opt_rm(char ***odb, int *nodb, int index);


/* --- compat -------------------------------------------------------------- */

#ifndef HAVE_STRLCPY
size_t	strlcpy(char *dst, const char *src, size_t siz);
#endif

#ifndef HAVE_STRLCAT
size_t	strlcat(char *dst, const char *src, size_t siz);
#endif

#ifndef HAVE_GETLINE
ssize_t	getline(char **__restrict buf, size_t *__restrict buflen,
		FILE *__restrict fp);
#endif

#endif /* H_GENOM */
