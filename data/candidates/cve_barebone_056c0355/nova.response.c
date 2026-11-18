static void xmlrpc_char_encode(char *buffer, char *arg) {
    struct config *cfp = current();
    char *cp = buffer;
    char *argp = arg;
    char fmt[200];
    char c;

    *cp = 0;
    if (argp == 0 || *argp == 0)
        return;
    for (;;) {
        c = *argp;
        if (c == 0)
            break;
        switch (c) {
        case '&':
            strcpy(cfp->value, "&");
            break;
        case '<':
            strcpy(cfp->value, "<");
            break;
        case '>':
            strcpy(cfp->value, ">");
            break;
        case '"':
            strcpy(cfp->value, "\"");
            break;
        default:
            cfp->value[0] = c;
            cfp->value[1] = 0;
        }
        sprintf(fmt, "%%s%s", cfp->type);
        asprintf(&cp, fmt, cfp->value);
    }
    strncpy(cfp->value, cp, 4096);
}