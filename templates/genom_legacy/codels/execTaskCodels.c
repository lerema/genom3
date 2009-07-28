<?
currentTask = comp.task(currentTaskName) # currentTaskName is set by genom
def codelNameToValue(n):
  if n == "MAIN":
     return "EXEC"
  elif n == "MAIN2":
     return "EXEC2"
  return n
?>
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

#include <stdlib.h>
#include <portLib.h>

#include "server/<!comp.name()!>Header.h"
#include "userCodels.h"
#include "../<!comp.name()!>UserStruct.h"

extern STATUS returnCodeToStatus(int res);

ACTIVITY_EVENT returnCodeToActivityEvent(int res)
{
  switch(res) {
<?
errorSet = create_error_list()
for e in errorSet:
    print "    case ERROR_" + e + ": return ETHER;"
for name, service in servicesDict.iteritems():
    if service.taskName != currentTaskName or service.type == Service.Control:
	continue

    # print targets for this service
    for c in service.codels():
	if c.key() == "control":
	    continue
	print "    case " + upper(service.name) + "_" + upper(c.key()) + ":  return " + codelNameToValue(upper(c.key())) + ";"
    # add the 'Ether' target
    print "    case " + upper(service.name) + "_ETHER: return ETHER;"
?>
    default:
	return ETHER;
  }
}

extern int returnCodeToReport(int res);

<?
alreadyDefinedCodels = []
for name, service in servicesDict.iteritems():
    if service.taskName != currentTaskName or service.type == Service.Control:
	continue
    for c in service.codels():
	if c.key() == "control":
	    continue
	codel = c.data()
	if codel.name in alreadyDefinedCodels: # some codels can be used twice (eg in stop and inter)
	    continue # do not define twice the same function
	alreadyDefinedCodels.append(codel.name)
	?>

extern <!real_codel_signature(codel, service)!>;

/*------------------------------------------------------------------------
 * <!codel.name!>_codel  -  control codel of EXEC request <!service.name!>
 *
 * Description:    
 * Report: OK
<?
	for m in service.errorMessages():
	    print " *   S_" + comp.name() + "_" + m
	?> *         
 *
 * Returns:    OK or ERROR
 */

<!codel_full_signature(c, service)!>
{
<?
	codel_lock(codel, service)
	?>

  /*call real codel */
  int res = <!real_codel_call(codel, service)!>;
  if(res < 0)
      *report = returnCodeToReport(res);

<?
	codel_release(codel, service)
	?>

  return returnCodeToActivityEvent(res);
}

<?
if currentTask.hasCodel("init"):
	?>
extern <!real_codel_signature(currentTask.codel("init"))!>;

/*------------------------------------------------------------------------
 *
 * <!currentTask.codel("init").name!>  --  Initialization codel (fIDS, ...)
 *
 * Description: 
 * 
 * Returns:    OK or ERROR
 */

STATUS <!codel_signature(currentTask.codel("init"))!>
{<?
	codel_lock(currentTask.codel("init"))
	?>

  /*call real codel */
  int res = <!real_codel_call(currentTask.codel("init"))!>;
  if(res < 0)
      *report = returnCodeToReport(res);

<?
	codel_release(currentTask.codel("init"))
	?>

  return returnCodeToStatus(res);
}
<?
?>

