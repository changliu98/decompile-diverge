char *strCpy(char *dest, char *src)
{
    char *destStart = dest;

    while(1)
    {
        *dest = *src;
        if( *dest == 0 )
            break;
        dest++;
        src++;
    }
    return destStart;
}