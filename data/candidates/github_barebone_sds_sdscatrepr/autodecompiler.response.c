char *sdscatrepr(char *buf, char *s, size_t len) {
    buf = sdscatlen(buf,"\"",1);
    while(len--) {
        switch(*s) {
        case '"': buf = sdscatprintf(buf,"\\%c",*s); break;
        case '\n': buf = sdscatlen(buf,"\\n",2); break;
        case '\r': buf = sdscatlen(buf,"\\r",2); break;
        case '\t': buf = sdscatlen(buf,"\\t",2); break;
        case '\a': buf = sdscatlen(buf,"\\a",2); break;
        case '\b': buf = sdscatlen(buf,"\\b",2); break;
        case '\\': buf = sdscatprintf(buf,"\\%c",*s); break;
        default:
            if (((*___ctype_b_loc ())[(int) ((*s))] & (unsigned short int) (0x4000)))
                buf = sdscatprintf(buf,"\\%c",*s);
            else
                buf = sdscatprintf(buf,"\\x%02x",(unsigned char)*s);
            break;
        }
        s++;
    }
    return sdscatlen(buf,"\"",1);
}