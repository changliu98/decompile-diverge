size_t func0(char *s, unsigned long long v) {
    char *p, aux;
    size_t t;

    
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);

    
    t = p-s;
    *p = '\0';

    
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return t;
}