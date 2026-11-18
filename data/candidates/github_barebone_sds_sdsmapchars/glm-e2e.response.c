sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen) {
    size_t len = sdslen(s);
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < setlen; j++) {
            if (s[i] == from[j]) {
                s[i] = to[j];
                break;
            }
        }
    }
    
    return s;
}