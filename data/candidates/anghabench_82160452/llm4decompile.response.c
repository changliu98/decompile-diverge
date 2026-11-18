int sdsll2str(char *s, long long value)
{
    char *p, aux;
    unsigned long long v;

    v = (value < 0) ? -(unsigned long long)value : (unsigned long long)value;
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    if (value < 0) *p++ = '-';
    *p-- = '\0';
    do {
        aux = *s;
        *s++ = *p;
        *p-- = aux;
    } while(s < p);
    return (int)(p-s);
}