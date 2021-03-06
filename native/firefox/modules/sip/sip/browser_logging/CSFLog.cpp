/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Cisco Systems SIP Stack.
 *
 * The Initial Developer of the Original Code is
 * Cisco Systems (CSCO).
 * Portions created by the Initial Developer are Copyright (C) 2002
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *  Enda Mannion <emannion@cisco.com>
 *  Suhas Nandakumar <snandaku@cisco.com>
 *  Ethan Hugg <ehugg@cisco.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "CSFLog.h"
#include "prlog.h"

static PRLogModuleInfo *gLogModuleInfo = NULL;

void CSFLogV(CSFLogLevel priority, const char* sourceFile, int sourceLine, const char* tag , const char* format, va_list args)
{
#ifdef STDOUT_LOGGING
  printf("%s\n:",tag);
  vprintf(format, args);
#else
  
#define MAX_MESSAGE_LENGTH 1024
  char message[MAX_MESSAGE_LENGTH];
    
  vsnprintf(message, MAX_MESSAGE_LENGTH, format, args);
  
  if (gLogModuleInfo == NULL)
    gLogModuleInfo = PR_NewLogModule("ikran");
    
  switch(priority)
  {
    case CSF_LOG_CRITICAL:
    case CSF_LOG_ERROR:
      PR_LOG(gLogModuleInfo, PR_LOG_ERROR, ("%s %s", tag, message));
      break;
    case CSF_LOG_WARNING:
    case CSF_LOG_INFO:
    case CSF_LOG_NOTICE:
      PR_LOG(gLogModuleInfo, PR_LOG_WARNING, ("%s %s", tag, message));
      break;
    case CSF_LOG_DEBUG:
      PR_LOG(gLogModuleInfo, PR_LOG_DEBUG, ("%s %s", tag, message));
      break;
    default:
      PR_LOG(gLogModuleInfo, PR_LOG_ALWAYS, ("%s %s", tag, message));
  }
  
#endif

}

void CSFLog( CSFLogLevel priority, const char* sourceFile, int sourceLine, const char* tag , const char* format, ...)
{
	va_list ap;
  va_start(ap, format);
	
  CSFLogV(priority, sourceFile, sourceLine, tag, format, ap);
  va_end(ap);
}

