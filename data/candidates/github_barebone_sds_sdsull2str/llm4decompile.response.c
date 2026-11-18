int sdsull2str(char *s,unsigned long long v) {
    char *p,*end;
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    *p = '\0';
    end = p;
    p = s;
    while(p<end--) {
        char aux = *p;
        *p = *end;
        *end = aux;
        p++;
    }
    return (int)(end-s);
}