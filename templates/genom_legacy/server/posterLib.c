/* 
 * Copyright (c) 2003 LAAS/CNRS
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

/*
 * Automatically generated by GenoM : do not edit by hand
 * Read data from the posters produced by the module <!comp.name()!>
 */


#include <stdio.h>
#include <stdlib.h>

#include <portLib.h>

#include "<!comp.name()!>PosterLib.h"
#include "<!comp.name()!>Print.h"
#include "<!comp.name()!>Endian.h"

#include <genom/h2endian.h>

/* Id. du poster de controle */
static POSTER_ID <!comp.name()!>CntrlPosterId=(POSTER_ID)NULL;
static H2_ENDIANNESS posterDataEndianness;

/*  prototypes de la bibliotheque printState */
extern char const * h2GetEvnStateString(int num);

/* ---------------- LE POSTER DE CONTROLE ------------------------------ */

/* ----------------------------------------------------------------------
 *
 *  <!comp.name()!>CntrlPosterRead - Lecture du poster de controle du module
 *
 */

POSTER_ID <!comp.name()!>CntrlPosterID () { return <!comp.name()!>CntrlPosterId; }

STATUS <!comp.name()!>CntrlPosterRead (<!upper(comp.name())!>_CNTRL_STR *<!comp.name()!>CntrlStrId)
{  
  if (!<!comp.name()!>CntrlPosterId)
    <!comp.name()!>CntrlPosterInit();
  if (posterRead (<!comp.name()!>CntrlPosterId, 0, (void *) <!comp.name()!>CntrlStrId, 
	      sizeof(<!upper(comp.name())!>_CNTRL_STR)) != sizeof(<!upper(comp.name())!>_CNTRL_STR))
    return ERROR; 
  return OK;
}

/* ---------------- LES POSTERS FONCTIONNELS ------------------------------ */

<?
for port in outports:
    print "static POSTER_ID " + port.name + "PosterId=(POSTER_ID)NULL;"
?>

/* -- posterInit ------------------------------------------------------- */

STATUS <!comp.name()!>PosterInit(void) {
  int status = OK;

  <!comp.name()!>RecordH2errMsgs();

  if (<!comp.name()!>CntrlPosterInit() == ERROR) {
    status = ERROR;  
  }
<?
for port in outports:?>
  if (<!comp.name()!><!port.name!>PosterInit() == ERROR) {
    status = ERROR;
  }<?
#endfor
?>
  return(status);
}


/* --  Cntrl ------------------------------------------------- */
STATUS <!comp.name()!>CntrlPosterInit(void)
{
  if (posterFind(<!upper(comp.name())!>_CNTRL_POSTER_NAME, &<!comp.name()!>CntrlPosterId) == ERROR) {
     h2perror("<!comp.name()!>CntrlPosterInit");
     return ERROR;
  }
  if (posterEndianness(<!comp.name()!>CntrlPosterId, &posterDataEndianness) == ERROR) {
    h2perror("<!comp.name()!>CntrlPosterInit");
    return ERROR;
  }
  return OK;
}


<?
for port in outports:
    ?>
/* --  <!port.name!> ------------------------------------------------- */

STATUS <!comp.name()!><!port.name!>PosterInit(void)
{
  if (posterFind(<!upper(comp.name())!>_<!upper(port.name)!>_POSTER_NAME, &<!port.name!>PosterId) == ERROR) {
     h2perror("<!comp.name()!><!port.name!>PosterInit");
     return ERROR;
  }
  if (posterEndianness(<!port.name!>PosterId, &posterDataEndianness) == ERROR) {
    h2perror("<!comp.name()!><!port.name!>PosterInit");
    return ERROR;
  }
  return OK;
}

/* --  <!port.name!>Read ------------------------------------------------- */

POSTER_ID <!comp.name()!><!port.name!>PosterID() { return <!port.name!>PosterId; }
STATUS <!comp.name()!><!port.name!>PosterRead(<!upper(comp.name())!>_<!upper(port.name)!>_POSTER_STR *x)
{
  if (<!port.name!>PosterId == (POSTER_ID)NULL) {
     if (<!comp.name()!><!port.name!>PosterInit() == ERROR) {
        h2perror("<!comp.name()!><!port.name!>PosterInit");
        return ERROR;
     }
  }
  if (posterRead(<!port.name!>PosterId, 0, (char *)x, sizeof(*x))
           != sizeof(*x)) {
    h2perror("<!comp.name()!><!port.name!>PosterRead:");
    return ERROR;
  }
  if (posterDataEndianness != H2_LOCAL_ENDIANNESS)
     endianswap_<!typeProtoPrefix(port.idlType)!>(x, 0, NULL);
  return OK;
}

/* --  <!port.name!> -> <!port.name!> ---------------------------------------- */
<?
#endfor
#todo read functiosn for poster elements
?>

