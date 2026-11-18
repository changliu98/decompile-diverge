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
        *p ^= *end;
        *end ^= *p;
        *p ^= *end;
        p++;
    }
    return (int)(end-s);
}