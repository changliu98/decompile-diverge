#include <stdio.h>

void escape(char s[], char t[])
{
 int i, j;

 i = j = 0;
 while (t[i] != '\0') {
  switch (t[i]) {
  case '\a':
   s[j] = '\\';
   ++j;
   s[j] = 'a';
   break;
  case '\b':
   s[j] = '\\';
   ++j;
   s[j] = 'b';
   break;
  case '\f':
   s[j] = '\\';
   ++j;
   s[j] = 'f';
   break;
  case '\n':
   s[j] = '\\';
   ++j;
   s[j] = 'n';
   break;
  case '\r':
   s[j] = '\\';
   ++j;
   s[j] = 'r';
   break;
  case '\t':
   s[j] = '\\';
   ++j;
   s[j] = 't';
   break;
  case '\v':
   s[j] = '\\';
   ++j;
   s[j] = 'v';
   break;
  case '\\':
   s[j] = '\\';
   ++j;
   s[j] = '\\';
   break;
  case '\?':
   s[j] = '\\';
   ++j;
   s[j] = '?';
   break;
  case '\'':
   s[j] = '\\';
   ++j;
   s[j] = '\'';
   break;
  case '\"':
   s[j] = '\\';
   ++j;
   s[j] = '\"';
   break;
  default:
   s[j] = t[i];
   break;
  }
  ++i;
  ++j;
 }
 s[j] = '\0';
}
