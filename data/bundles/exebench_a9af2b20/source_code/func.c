
char* stpCpy(char* dest, const char* src)
{

    while ( (*dest = *src++) )
        dest++;

    return dest;
}
