#include <stdio.h>

#include <strings.h>

#include <stdlib.h>

void find_ibm( int char1, int char2,
       int * outchar1, int * outchar2 )
{
  int rno, tmp1, tmp2;

  rno = (char1 - 161) * 157 + char2 - 63-(char2>126)?34:0;
  rno += (rno>408)?93:0;
  tmp1 = (rno % 188) + 137;
  tmp2 = (rno - ((rno % 188) * 188))+63;
  if( tmp2 > 126 )
    tmp2++;
  *outchar1 = tmp1;
  *outchar1 = tmp2;
  return;
}
