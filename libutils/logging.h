/*
   Copyright (C) CFEngine AS

   This file is part of CFEngine 3 - written and maintained by CFEngine AS.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 3.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

  To the extent this program is licensed as part of the Enterprise
  versions of CFEngine, the applicable Commercial Open Source License
  (COSL) may apply to this file if you as a licensee so wish it. See
  included file COSL.txt.
*/

#ifndef CFENGINE_LOGGING_H
#define CFENGINE_LOGGING_H

#include <platform.h>
#include <compiler.h>

// Does not include timezone, since it is hard to match on Windows.
#define LOGGING_TIMESTAMP_REGEX "^20[0-9][0-9]-[01][0-9]-[0-3][0-9]T[0-2][0-9]:[0-5][0-9]:[0-5][0-9]"

typedef enum
{
    LOG_LEVEL_NOTHING = -1,
    LOG_LEVEL_CRIT,
    LOG_LEVEL_ERR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_DEBUG
} LogLevel;

const char *LogLevelToString(LogLevel level);

/**
 * @brief Return the standard timestamp format used in logging.
 * @param dest Output buffer
 * @param n size of output buffer
 * @param timestamp Timespec to format
 * @return True if successful, otherwise "<unknown>" will be printed to buffer
 */
bool LoggingFormatTimestamp(char dest[64], size_t n, struct tm *timestamp);


void Log(LogLevel level, const char *fmt, ...) FUNC_ATTR_PRINTF(2, 3);
void LogRaw(LogLevel level, const char *prefix, const void *buf, size_t buflen);
void VLog(LogLevel level, const char *fmt, va_list ap);

void LogSetGlobalLevel(LogLevel level);
LogLevel LogGetGlobalLevel(void);

void LoggingSetColor(bool enabled);

/*
 * Portable strerror(errno)
 */
const char *GetErrorStr(void);
const char *GetErrorStrFromCode(int error_code);

#endif
