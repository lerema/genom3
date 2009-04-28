
/* 
 * Copyright (c) 1993-2005 LAAS/CNRS
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

/*--------------  file automaticaly generated with GenoM -------------*/
/*-----------------------  DO NOT EDIT BY HAND -----------------------*/
 
/****************************************************************************/
/*   LABORATOIRE D'AUTOMATIQUE ET D'ANALYSE DE SYSTEMES - LAAS / CNRS       */
/*   PROJET HILARE II - INTERACTION PAR POSTER AVEC LE MODULE  <!upper(comp.name())!>     */
/*   FICHIER SOURCE : "<!comp.name()!>PosterLib.c"                                 */
/****************************************************************************/

/* DESCRIPTION :
   Bibliotheque de fonctions qui permettent la lecture ou l'affichage
   du contenu des posters du module
*/


#include <stdio.h>
#include <stdlib.h>
#include <portLib.h>

#include "<!comp.name()!>PosterShowLib.h"
#include "<!comp.name()!>Print.h"


<?
# $execTaskNameTabDeclare$
write("static char *" + comp.name() + "ExecTaskNameTab[] = {\n");
task_list = ""
for t in comp.tasksMap():
    task_list += "\"" + t.data().name + "\",\n"
print task_list[:-2] # remove the last ',' 
print "};"
?>

/*  prototypes de la bibliotheque printState */
extern char const * h2GetEvnStateString(int num);

static void <!comp.name()!>ActivityShow (<!upper(comp.name())!>_CNTRL_STR *sdic);


/* ---------------- LE POSTER DE CONTROLE ------------------------------ */

/* ----------------------------------------------------------------------
 *
 *  <!comp.name()!>CntrlPosterShow - Affichage du poster de controle du module
 *
 */

STATUS <!comp.name()!>CntrlPosterShow ()
{
  char strmsg[64];
  <!upper(comp.name())!>_CNTRL_STR *sdic;
  int i;

  /* Lecture de la SDI de controle */
  sdic = (<!upper(comp.name())!>_CNTRL_STR *)malloc(sizeof(<!upper(comp.name())!>_CNTRL_STR));
  if (sdic == NULL) {
    h2perror ("<!comp.name()!>CntrlPosterShow");
    return ERROR;
  }
  if (<!comp.name()!>CntrlPosterRead (sdic) != OK) {
    free(sdic);
    return ERROR;
  }

  /* 
   * Affichage 
   */

  printf ("-- TASKS           (status)      (last duration)         (bilan)\n");
  /* Tache de controle */
  printf (" Control Task        %-5s                               %s\n",  
	  M_CNTRL_TASK_STATUS(sdic)==OK ? "OK":"ERROR",
	  h2getErrMsg(M_CNTRL_TASK_BILAN(sdic), strmsg, 64));
  
  /* Taches d'execution */
  for (i=0; i<<!upper(comp.name())!>_NB_EXEC_TASK; i++) {
    printf (" %d:%-15s   %-5s ",  
	    i, <!comp.name()!>ExecTaskNameTab[i],
	    M_EXEC_TASK_STATUS(sdic,i) == OK ? "OK": "ERROR");
    if (M_EXEC_TASK_PERIOD(sdic,i) != 0) {
      printf ("    %3lums ", M_EXEC_TASK_ON_PERIOD(sdic,i));
      printf ("(max %lu, ", M_EXEC_TASK_MAX_PERIOD(sdic,i));
      printf ("th %d)", (int)(M_EXEC_TASK_PERIOD(sdic,i)*1000.));
    }
    else {
      printf ("    %3lums ", M_EXEC_TASK_ON_PERIOD(sdic,i));
      printf ("(max %lu)        ", M_EXEC_TASK_MAX_PERIOD(sdic,i));      
    }
    printf ("\t %s\n", h2getErrMsg(M_EXEC_TASK_BILAN(sdic,i), strmsg, 64));

  }
  printf ("\n");

  /* Activites */
  <!comp.name()!>ActivityShow (sdic);

  free(sdic);
  return OK;
}

STATUS <!comp.name()!>CntrlPosterActivityShow ()
{
  <!upper(comp.name())!>_CNTRL_STR *sdic;

  /* Lecture de la SDI de controle */
  sdic = (<!upper(comp.name())!>_CNTRL_STR *)malloc(sizeof(<!upper(comp.name())!>_CNTRL_STR));
  if (sdic == NULL) {
    h2perror ("<!comp.name()!>CntrlPosterActivityShow");
    return ERROR;
  }
  if (<!comp.name()!>CntrlPosterRead (sdic) != OK) {
    free(sdic);
    return ERROR;
  }

  <!comp.name()!>ActivityShow (sdic);

  free(sdic);
  return OK;
}

/* Fonciton locale d'affichage des activitées */
static void <!comp.name()!>ActivityShow (<!upper(comp.name())!>_CNTRL_STR *sdic)
{
#define <!upper(comp.name())!>_NB_RQST_EXEC <!nbExecService()!>
#if <!upper(comp.name())!>_NB_RQST_EXEC != 0

<? #  $requestNameTabDeclare$
write("static char *" + comp.name() + "ExecRqstNameTab[] = {\n");
service_list = ""
for s in comp.servicesMap():
    if s.data().type != ServiceType.Control:
	service_list += "\"" + s.data().name + "\",\n"
print service_list[:-2] # remove the last ',' 
print "};"

print "static int " + comp.name() + "ExecRqstNumTab[] = {"
i = 0
l = ""
for s in comp.servicesMap(): 
    if s.data().type != ServiceType.Control:
	l +=  str(i) + ", "
    i += 1
print l[:-2] + "};"
?>
  int i,oneActivity=FALSE;
  ACTIVITY_EVENT evn;
  ACTIVITY_STATE status;
  int bilan;
  int rqst;
  char strmsg[64];
  
  /*  printf (" ACTIVITY  REQUEST         TASK        FROM -> TO    BILAN\n");*/
  printf ("-- ACTIVITIES\n");
  for (i=0; i<MAX_ACTIVITIES; i++) {
    status = M_ACTIVITY_STATUS(sdic,i);
    bilan = M_ACTIVITY_BILAN(sdic,i);

    /* Affichage */
    if (status != ETHER || bilan != OK) {
      evn = M_ACTIVITY_EVN(sdic,i);
      
      /* Identification de la requete */
      rqst=0;
      while(<!comp.name()!>ExecRqstNumTab[rqst] != M_ACTIVITY_RQST_TYPE(sdic,i) 
	    && rqst<<!upper(comp.name())!>_NB_RQST_EXEC)
	rqst++;

      if (status != ETHER) 
	oneActivity = TRUE;

      printf ("%s%2d  %2d:%-10s    %-10s\t%5s %s%s\n", 
	      status == ETHER ? " (" : "  ",

	      M_ACTIVITY_ID(sdic,i), 

	      rqst == <!upper(comp.name())!>_NB_RQST_EXEC ? 
	      M_ACTIVITY_RQST_TYPE(sdic,i) : <!comp.name()!>ExecRqstNumTab[rqst],

	      rqst == <!upper(comp.name())!>_NB_RQST_EXEC?
	      "Unknown" : <!comp.name()!>ExecRqstNameTab[rqst], 
	      
	      M_ACTIVITY_TASK_NUM(sdic,i) == -1 ? 
	      "not exec" : <!comp.name()!>ExecTaskNameTab[M_ACTIVITY_TASK_NUM(sdic,i)], 
	      
	      evn == NO_EVENT ?
	      h2GetEvnStateString(status) : h2GetEvnStateString(evn), 

	      h2getErrMsg(bilan, strmsg, 64),
	      
	      status == ETHER ? ")" : "");
    }

  }	/* for */
  if (!oneActivity) printf ("  No activity\n");
#endif /* <!upper(comp.name())!>_NB_RQST_EXEC != 0 */
}

/* ---------------- LES POSTERS FONCTIONNELS ------------------------------ */

<?
for p in outports:
    poster_type = upper(comp.name()) + "_" + upper(p.name) + "_POSTER_STR"
    ?>
/* --  <!p.name!> ------------------------------------------------- */

STATUS <!comp.name()!><!p.name!>PosterShow(void)
{
  <!poster_type!> *x;

  if ((x = (<!poster_type!> *)malloc(sizeof(* x))) == NULL) {
     h2perror("<!comp.name()!><!p.name!>PosterShow");
     return ERROR;
  }
  if (<!comp.name()!><!p.name!>PosterRead(x) == ERROR) {
     h2perror("<!comp.name()!><!p.name!>PosterShow");
     free(x);
     return ERROR;
  }
  print_<!typeProtoPrefix(p.idlType)!>(stdout, x, 0, 0, NULL, stdin);
  free(x);
  return OK;
}
<?
?>
