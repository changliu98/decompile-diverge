
char* strCpy(char* dest, const char* src)
{
    char* destStart = dest;


    while ( (*dest++ = *src++) )
        ;

    return destStart;
}
