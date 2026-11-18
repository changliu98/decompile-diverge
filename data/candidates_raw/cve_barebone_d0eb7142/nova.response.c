int func0(struct s_command *c, const char *s, const char *e) {
    int i;
    const char *p;
    char q;

    if (!c)
        i = 2;
    else {
        c->c_type = 0;
        c->c_flags = 0;
        c->c_name[0] = 0;
        if (!s ||!e)
            i = 2;
        else {
            for (p = s; p < e; p++) {
                if (p == s && *p == '<')
                    q = '<';
                else if (p == s && *p == '>')
                    q = '>';
                else
                    q = '<';
                if (p + 1 > e)
                    i = 2;
                else if (memcmp(p, "<<<", 3) == 0 || memcmp(p, ">>>", 3) == 0) {
                    if (*p == '>')
                        i = 2;
                    else
                        i = 0;
                    while (*p == '<' || *p == '>')
                        p++;
                    c->c_type = *p;
                    c->c_name[i++] = 0;
                    break;
                } else if (*p == '/') {
                    p++;
                    i = -1;
                    break;
                }
            }
        }
    }
    for (; p < e; p++)
        c->c_name[i++] = *p;
    c->c_name[i] = 0;
    return i;
}