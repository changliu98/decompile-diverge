char * _xtoa(unsigned long num, char *str, int base, int sign)
{
    char * rc;
    char * ptr;
    char * low;


    if ( str == 0 )
    {
        str = (char *)(long)(&rc[1]);
    }

    rc = ptr = &str[24];

    low = ptr;


    do
    {

        *ptr++ = "0123456789abcdef"[num % base];
        num /= base;
    } while ( num );


    if ( sign )
    {
        *ptr++ = '-';
    }


    while ( low != ptr )
    {
        --ptr;

        *str++ = *ptr;
    }

    *str = '\0';

    return rc;
}