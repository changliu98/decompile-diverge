sds sdscpylen(sds s, char *t, size_t len) {
    struct sdshdr *sh;
    size_t totlen, curlen;

    if (sdsalloc(s) < len) {
        sh = (void*)s-(sizeof(struct sdshdr));
        totlen = sh->free+sh->len;
        s = sdsMakeRoomFor(s, len-sdslen(s));
        if (s == NULL) return NULL;
        sh = (void*)s-(sizeof(struct sdshdr));
        curlen = totlen-sh->free;
    } else {
        curlen = sdslen(s);
    }
    memcpy(s,t,len);
    s[len] = '\0';
    sdssetlen(s,len);
    return s;
}