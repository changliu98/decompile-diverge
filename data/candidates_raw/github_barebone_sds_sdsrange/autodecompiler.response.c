void sdsIncrLen(sds s, int incr) {
    sdshdr *sh = (void*) s - (sizeof(sdshdr));

    sh->len += incr;
    sh->free -= incr;
    s[sdslen(s)] = '\0';
}