#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <string.h>

char *ReadNumber(char *s,double *num)
{
    double x3,minus = 1;
    int x1,x2;
    while ( *s == '+' || *s == '-' ) {
        if ( *s == '-' ) minus = -minus;
        s++;
    }
    x1 = x2 = 0; x3 = 1;
    while ( *s <= '9' && *s >= '0' ) { x1 = 10*x1 + *s++ - '0'; }
    if ( *s == 0 ) { *num = x1*minus; return(s); }
    if ( *s == '.' ) {
        s++;
        while ( *s >= '0' && *s <= '9' ) { x2 = 10*x2 + *s++ - '0'; x3 *= 10; }
    }
    *num = minus*((double)x1 + x2/x3);
    return(s);
}
