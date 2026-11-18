#include <stdio.h>

#include <stdarg.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>

static void toup( char *chr_ptr)
{
    const unsigned char upcas_diff = ( 'a' - 'A' );
    if ( ( *chr_ptr >= 'a' ) && ( *chr_ptr <= 'z' ) )
    {
 *chr_ptr -= upcas_diff ;
    }
}
