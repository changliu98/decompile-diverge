sds sdscpylen(sds s, const char *t, size_t len) {
    size_t totlen, curlen;

    sdsalloc(s);
    totlen = sdsalloc(s)+(len-sdslen(s));
    if (totlen < len) {
        s = sdsMakeRoomFor(s,len-sdslen(s));
        if (s == NULL) return NULL;
    }
    memcpy(s, t, len);
    s[len] = '\0';
    sdssetlen(s, len);
    return s;
}