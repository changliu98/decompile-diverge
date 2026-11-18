int func0(char *buf, int flags, char c) {
    int i;
    char ch = c;

    while (1) {
        switch (ch) {
        case '\b':
            if (flags & FLAG_BACKSPACE) {
                buf[0] = '\b';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        case '\n':
            if (flags & FLAG_NEWLINE) {
                buf[0] = '\n';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        case '\r':
            if (flags & FLAG_CARRIAGERETURN) {
                buf[0] = '\r';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        case '\t':
            if (flags & FLAG_TAB) {
                buf[0] = '\t';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        case '\a':
            if (flags & FLAG_ALERT) {
                buf[0] = '\a';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        case '\v':
            if (flags & FLAG_VERTICALTAB) {
                buf[0] = '\v';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        case '\f':
            if (flags & FLAG_FORMFEED) {
                buf[0] = '\f';
                i = 1;
            } else {
                buf[0] = ch;
                i = 1;
            }
            break;
        default:
            buf[0] = ch;
            i = 1;