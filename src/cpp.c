/*
 * Copyright (c) 2009-2012,2017-2018,2022-2023 LAAS/CNRS
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
#include "acgenom.h"

#include <sys/param.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include <err.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include "genom.h"


/* --- local data ---------------------------------------------------------- */

/** options array to pass to cpp */
static char **cppopts = NULL;

/** number of options */
static int ncppopts = 0;

/** pid of lastest cpp process */
static pid_t cpppid = -1;


/* --- cpp_optappend ------------------------------------------------------- */

int
cpp_optappend(const char *opt, int index)
{
  int s = opt_append(&cppopts, &ncppopts, opt, index);
  if (s) {
    warnx("failed to add cpp option `%s'", opt);
    return s;
  }

  xwarnx("added cpp option `%s'", opt);
  return 0;
}


/* --- cpp_optrm ----------------------------------------------------------- */

int
cpp_optrm(int index)
{
  return opt_rm(&cppopts, &ncppopts, index);
}


/* --- cpp_invoke ---------------------------------------------------------- */

/** Call cpp on input file
 */

int
cpp_invoke(char *in[], int out)
{
  char inpath[PATH_MAX];
  char *cpp, *p;
  int noptexec;
  FILE *infile;
  int cwd;
  int s, n;

  /* get cpp executable */
  cpp = strdup(runopt.cpppath);
  if (!cpp || cpp[0] == '\0') {
    warnx("memory exhausted, cannot run cpp");
    return ENOMEM;
  }

  /* split executable into options array */
  for(noptexec=0, p = cpp; *p != '\0'; noptexec++) {
    n = strcspn(p, " \t");
    if (p[n] != '\0') {
      p[n] = '\0';
      s = cpp_optappend(p, noptexec);
      p += n+1;
    } else {
      s = cpp_optappend(p, noptexec);
      p += n;
    }
    if (s) {
      warnx("memory exhausted, cannot run cpp");
      free(cpp);
      errno = ENOMEM; goto err;
    }
  }
  free(cpp);

  /* setup input file containing the #include'd list of input */
  n = snprintf(inpath, sizeof(inpath), "%s/input.c", runopt.tmpdir);
  if (n >= sizeof(inpath)) {
    warnx("%s: filename too long", inpath);
    errno = ENAMETOOLONG; goto err;
  }
  infile = fopen(inpath, "w");
  if (!infile) {
    warnx("cannot cate %s input file", inpath); warn(NULL);
    errno = EIO; goto err;
  }

  /* temporarily change to -C directory */
  if (*runopt.dgpath) {
    cwd = open(".", O_RDONLY);
    if (cwd < 0) { warn("cannot open directory '.'"); goto err; }
    if (chdir(runopt.dgpath)) { warn("%s", runopt.dgpath); goto err; }
    xwarnx("changed directory to '%s'", runopt.dgpath);
  } else cwd = -1;

  /* resolve all input files */
  for(; *in; in++) {
    char rpath[PATH_MAX];

    if (!realpath(*in, rpath)) { warn("%s", *in); goto err; }

    fprintf(infile, "#include \"%s\"\n", rpath);
    xwarnx("resolved '%s' as '%s'", *in, rpath);
  }

  /* undo -C */
  if (cwd >= 0) {
    if (fchdir(cwd)) { warn("cannot chdir '.'"); goto err; }
    close(cwd);
    xwarnx("changed directory to '.'");
  }

  fclose(infile);
  xwarnx("created input file `%s'", inpath);

  s = cpp_optappend(inpath, -1);
  if (s) {
    warnx("memory exhausted, cannot run cpp");
    errno = ENOMEM; goto err;
  }

  /* execvp cpp */
  if (runopt.verbose) {
    char **o;
    xwarnx("spawning cpp with the following arguments:");
    for(o = cppopts; *o; o++) xwarnx("  + %s", *o);
  }

  switch((cpppid = vfork())) {
    case -1:
      warnx("unable to fork cpp"); warn(NULL);
      cpp_optrm(-1);
      errno = EAGAIN; goto err;

    case 0: /* child */
      if (out != fileno(stdout)) {
	if (dup2(out, fileno(stdout)) < 0) {
	  warnx("unable to set cpp stdout"); warn(NULL);
	  _exit(2);
	}
	close(out);
      }

      s = execvp(cppopts[0], cppopts);
      if (s) { warnx("unable to exec '%s'", cppopts[0]); warn(NULL); }
      _exit(127);

    default: /* parent */
      if (out != fileno(stdout)) close(out);
      break;
  }

  /* clean up */
  for(;noptexec>0; noptexec--) cpp_optrm(0);
  cpp_optrm(-1);
  return 0;
err:
  for(;noptexec>0; noptexec--) cpp_optrm(0);
  return errno;
}


/* --- cpp_getnotice ------------------------------------------------------- */

/** Read input file and look for the special "copyright notice" token. Return a
 * string that is the content of the corresponding C comment (or
 * NULL). #include directive are not processed, and only the first match is
 * returned. No error is ever reported: the notice is optional.
 *
 * Interestingly, that special symbol cannot be put in a C comment except at
 * the very beginning, so the syntax is documented right after the present
 * comment ;)
 */
/*/ <- here! */
char *
cpp_getnotice(const char *in)
{
  char *notice = NULL;
  FILE *f;
  char *line;
  size_t l;
  char *p, *w;
  int cwd;
  int inside;

  /* temporarily change to -C directory */
  if (*runopt.dgpath) {
    cwd = open(".", O_RDONLY);
    if (cwd < 0) return NULL;
    if (chdir(runopt.dgpath)) return NULL;
    xwarnx("changed directory to '%s'", runopt.dgpath);
  } else cwd = -1;

  f = fopen(in, "r");
  if (!f) return NULL;

  if (cwd >= 0) {
    if (fchdir(cwd)) return NULL;
    close(cwd);
    xwarnx("changed directory to '.'");
  }

  line = NULL;
  l = 0;
  inside = 0;
  while(1) {
    /* read one line of input */
    if (getline(&line, &l, f) == -1) break;

    p = line;
    switch(inside) {
      case 0:
	/* look for the special token */
	p = strstr(p, "/*/"); if (!p) break;
	inside = 1;

	/* set text pointer to the end of the token, replacing the last / with
	 * a space except before a newline (so that text alignment within the
	 * comment is kept) */
	p += 2;
        if (p[1] == '\n') p++; else *p = ' ';

	/*FALLTHROUGH*/
      case 1:
	/* replace final delimiter with a \0 */
	w = strstr(p, "*/");
	if (w) { *w = '\0'; inside = 0; }

	/* transform every \n followed by spaces and any number of stars by a
	 * simple \n (this tidy multi-line comment with * decorations)
	 */
	w = p;
	while(*p == ' ' || *p == '	') p++;
	if (*p == '\0') break;
	if (*p != '*') p = w; else { while(*p == '*') p++; }

	bufcat(&notice, "%s", p);
	break;
    }

    /* stop after first block */
    if (!inside && notice) break;
  }
  if (inside) {
    xwarnx("unterminated special copyright notice comment");
    free(notice);
    notice = NULL;
  }
  if (line) free(line);
  fclose(f);

  if (notice) xwarnx("found special copyright notice comment");
  return notice;
}


/* --- cpp_wait ------------------------------------------------------------ */

/** Wait for cpp process
 */

int
cpp_wait()
{
  int status;

  waitpid(cpppid, &status, 0);
  if ((!WIFEXITED(status) || WEXITSTATUS(status))) {
    if (WIFSIGNALED(status)) {
      warnx("cpp process exited with signal %d", WTERMSIG(status));
      return 127;
    }
    warnx("cpp process exited with code %d", WEXITSTATUS(status));
    return WEXITSTATUS(status);
  }

  xwarnx("cpp process exited with code %d", WEXITSTATUS(status));
  return 0;
}
