char* strcpy(char *s1, const char *s2)
{
    char* p = s1;
    int f;
    do{
        f = (*s1++ = *s2++);
    }
    while(f);
    return p;
}