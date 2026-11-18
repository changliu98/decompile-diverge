#include <ctype.h> /* tolower() isspace() */

#include <limits.h> /* INT_MAX INT_MIN LONG_MAX LONG_MIN */

#include <stdarg.h> /* va_list va_start() va_copy() va_end() */

#include <stddef.h> /* NULL size_t wchar_t */

#include <stdio.h> /* snprintf() */

#include <stdlib.h> /* free() malloc() mbstowcs() realloc() strtol()

#include <string.h> /* strncmp() strlen() strcmp() strchr() strrchr()

#include <wchar.h> /* vswprintf() */

#include <wctype.h> /* towlower() iswupper() */

void
break_at(char str[], char c)
{
 char *const p = strchr(str, c);
 if(p != NULL)
 {
  *p = '\0';
 }
}
