#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <inttypes.h>

#include <stdbool.h>

#include <assert.h>

unsigned int utf8_decode_v2(const char *utf8char, size_t size, size_t *charlen)
{
 if(size == 0 || utf8char[0] == 0)
 {
  if(charlen)
   *charlen = 0;

  return 0xFFFFFFFF;
 }
 else if((utf8char[0] & 0x80) == 0x00)
 {
  if(charlen)
   *charlen = 1;

  return (unsigned int)(utf8char[0] & 0x7F);
 }
 else if((utf8char[0] & 0xE0) == 0xC0)
 {
  if(charlen)
   *charlen = 2;
  if(size < 2 || utf8char[1] == 0)
   return 0xFFFFFFFF;

  return (unsigned int)(
    ((utf8char[0] & 0x1F) << 6) |
    (utf8char[1] & 0x3F)
   );
 }
 else if((utf8char[0] & 0xF0) == 0xE0)
 {
  if(charlen)
   *charlen = 3;
  if(size < 3 || utf8char[1] == 0 || utf8char[2] == 0)
   return 0xFFFFFFFF;

  return (unsigned int)(
    ((utf8char[0] & 0x0F) << 12) |
    ((utf8char[1] & 0x3F) << 6) |
    (utf8char[2] & 0x3F)
   );
 }
 else if((utf8char[0] & 0xF8) == 0xF0)
 {
  if(charlen)
   *charlen = 4;
  if(size < 4 || utf8char[1] == 0 || utf8char[2] == 0 || utf8char[3] == 0)
   return 0xFFFFFFFF;

  return (unsigned int)(
    ((utf8char[0] & 0x07) << 15) |
    ((utf8char[1] & 0x3F) << 12) |
    ((utf8char[2] & 0x3F) << 6) |
    (utf8char[3] & 0x3F)
   );
 }
 else
 {
  if(charlen)
   *charlen = 0;

  return 0xFFFFFFFF;
 }
}
