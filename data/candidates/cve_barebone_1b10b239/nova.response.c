int read_new_config_info(struct s_node *c, struct s_node *p) {
    int i, j;
    int len = p->len;
    char *s = p->s;

    c->flag = 1;
    c->v = 0;
    c->c = 0;
    c->s[0] = 0;
    while (len) {
        while (len &&!s[0]) {
            s++;
            len--;
        }
        if (!len)
            break;
        c->v += s[0];
        len--;
        if (!len)
            break;
        c->c += s[0];
        len--;
        if (!len)
            break;
        c->s[0] = s[0];
        len--;
        while (len) {
            if (len < c->c)
                break;
            c->s[++i] = s[++j];
            len--;
        }
        if (len)
            break;
        c->v += c->c;
    }
    return i;
}