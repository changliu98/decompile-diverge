void string_reverse (char *p) {
    char *q = p;
    while(q && *q) ++q;
    for(--q; p < q; ++p, --q) (*p^=*q, *q^=*p, *p^=*q);
}