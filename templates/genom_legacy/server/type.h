/* 
 * Copyright (c) 1993-2003 LAAS/CNRS
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

/*------------------  Fichier généré automatiquement ------------------*/
/*------------------  Ne pas éditer manuellement !!! ------------------*/

/* 
 * <!comp.name()!>Type.h:     La SDI_F de <!comp.name()!>
 *
 * Utilise par le module et par les clients
 * (inclut dans <!comp.name()!>MsgLib.h et <!comp.name()!>PosterLib.h)
 * 
 */

#ifndef <!comp.name()!>_TYPE_H
#define <!comp.name()!>_TYPE_H

#include "genom/modules.h"
#include "<!comp.name()!>Error.h"

/* Nombre de tache d'execution de ce module */
#define <!upper(comp.name())!>_NB_EXEC_TASK                   (<!str(len(comp.tasksMap()))!>)

#endif

#ifndef <!comp.name()!>_TYPE1_H
#define <!comp.name()!>_TYPE1_H

#include "<!comp.name()!>Struct.h"

<?
t = comp.IDSType.unalias()
print t.toCType() + ";"
print "typedef " + comp.IDSType.toCType() + " " + upper(comp.name()) + "_STR;";
?>

#endif
