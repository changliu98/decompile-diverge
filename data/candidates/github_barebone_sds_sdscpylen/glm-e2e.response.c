sds sdscpylen(sds s, const char *t, size_t len) {
    if (sdsalloc(s) < len) {
        sds new_s = sdsMakeRoomFor(s, len - sdslen(s));
        if (new_s == NULL) {
            return NULL;
        }
        s = new_s;
    }
    
    memcpy(s, t, len);
    s[len] = '\0';
    sdssetlen(s, len);
    
    return s;
}