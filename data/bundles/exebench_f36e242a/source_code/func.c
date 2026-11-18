
int ltos( char *s, long num ) {



    char buf[20], *p;

    unsigned long anum;

    p = buf;




    anum = ( num < 0 ) ? -num : num;




    while( anum > 9 ) {
        *p++ = '0' + ( anum % 10 );
        anum /= 10;
    }




    if( num < 0 ) {
        *s++ = '-';
    }




    *s++ = '0' + ( char ) anum;




    while( p-- > buf ) {
        *s++ = *p;
    }




    *s = '\0';
    return 0;
}
