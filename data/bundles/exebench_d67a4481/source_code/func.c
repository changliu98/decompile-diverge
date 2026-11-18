#include <stdio.h>

#include <string.h>

#include <stdint.h>

int Utf8ToUnicode(char *utf8char, int* unicode, int *len, size_t leaveLen) {
  char cTmp = *utf8char;
  if ((cTmp & 0xF8) == 0xF0) {
   if (leaveLen < 4 || (((*(utf8char + 1)) & 0xC0) != 0x80) || (((*(utf8char + 2)) & 0xC0) != 0x80) || (((*(utf8char + 3)) & 0xC0) != 0x80)) {
    return 2;
   }
   *len = 4;
   *unicode |= (cTmp & 0x07);
   *unicode <<= 6;

   cTmp = *(utf8char + 1);
   *unicode |= (cTmp & 0x3F);
   *unicode <<= 6;

   cTmp = *(utf8char + 2);
   *unicode |= (cTmp & 0x3F);
   *unicode <<= 6;

   cTmp = *(utf8char + 3);
   *unicode |= (cTmp & 0x3F);
  }
  else if ((cTmp & 0xF0) == 0xE0) {
   if (leaveLen < 3 || (((*(utf8char + 1)) & 0xC0) != 0x80) || (((*(utf8char + 2)) & 0xC0) != 0x80)) {
    return 2;
   }
   *len = 3;
   *unicode |= (cTmp & 0x0F);
   *unicode <<= 6;

   cTmp = *(utf8char + 1);
   *unicode |= (cTmp & 0x3F);
   *unicode <<= 6;

   cTmp = *(utf8char + 2);
   *unicode |= (cTmp & 0x3F);
  }
  else if ((cTmp & 0xE0) == 0xC0) {
   if (leaveLen < 2 || (((*(utf8char + 1)) & 0xC0) != 0x80)) {
    return 2;
   }
   *len = 2;
   *unicode |= (cTmp & 0x1F);
   *unicode <<= 6;

   cTmp = *(utf8char + 1);
   *unicode |= (cTmp & 0x3F);
  }
  else if ((cTmp & 0x80) == 0x00) {
   *len = 1;
   *unicode = cTmp;
  }
  else {
   return 1;
  }
  return 0;
 }
