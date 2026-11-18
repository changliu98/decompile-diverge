#include <stdio.h>

void reverse( char *str ) {
  char *q = str;
  while ( *q++ )
    ;
  q -= 2;
  for ( ; str < q; str++, q-- ) {
    *str -= *q;
    *q += *str;
    *str = *q - *str;
  }
}
