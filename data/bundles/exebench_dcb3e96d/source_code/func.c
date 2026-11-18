#include <stdio.h>

void utf8_encode( int val, char *utf8_str )
{
  int len = 0;

  if ( val >= 0x0000 && val <= 0x007f ) {

    utf8_str[0] = 0x7F & val;
    len = 1;
  }
  else if ( val >= 0x0080 && val <= 0x07ff ) {

    utf8_str[1] = ( ( val & 0x3f ) | 0x80 );
    val = val >> 6;
    utf8_str[0] = ( ( val & 0x1f ) | 0xc0 );
    len = 2;
  }
  else if ( val >= 0x0800 && val <= 0xffff ) {

    utf8_str[2] = ( ( val & 0x3f ) | 0x80 );
    val = val >> 6;
    utf8_str[1] = ( ( val & 0x3f ) | 0x80 );
    val = val >> 6;
    utf8_str[0] = ( ( val & 0x0f ) | 0xe0 );
    len = 3;
  }
  else if ( val >= 0x10000 && val <= 0x10FFFF ) {

    utf8_str[3] = ( ( val & 0x3f ) | 0x80 );
    val = val >> 6;
    utf8_str[2] = ( ( val & 0x3f ) | 0x80 );
    val = val >> 6;
    utf8_str[1] = ( ( val & 0x3f ) | 0x80 );
    val = val >> 6;
    utf8_str[0] = ( ( val & 0x07 ) | 0xF0 );
    len = 4;
  }

  utf8_str[len] = '\0';
}
