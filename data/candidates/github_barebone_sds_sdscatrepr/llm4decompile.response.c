sds sdscatrepr(sds s, const char *p, size_t len) {
    s = sdscatlen(s,"\"",1);
    while(len--) {
        if (*p == '\a') { s = sdscatlen(s,"\\a",2); }
        else if (*p == '\b') { s = sdscatlen(s,"\\b",2); }
        else if (*p == '\f') { s = sdscatlen(s,"\\f",2); }
        else if (*p == '\n') { s = sdscatlen(s,"\\n",2); }
        else if (*p == '\r') { s = sdscatlen(s,"\\r",2); }
        else if (*p == '\t') { s = sdscatlen(s,"\\t",2); }
        else if (*p == '\v') { s = sdscatlen(s,"\\v",2); }
        else if (*p == '\\' || *p == '"') { s = sdscatprintf(s,"\\%c",*p); }
        else if ((*p >= 0 && *p <= 31) || (*p > 126)) { s = sdscatprintf(s,"\\x%02x",(unsigned char)*p); }
        else { s = sdscatprintf(s,"%c",*p); }
        p++;
    }
    return sdscatlen(s,"\"",1);
}