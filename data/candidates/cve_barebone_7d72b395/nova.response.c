int read_new_config_info(struct s_node *c, struct s_node *p) {
    int i, j, k;
    int l;
    int r;
    int s;
    int t;
    int u;
    int v;
    int w;

    assert(c);

    l = p->len;
    c->flag = 1;
    c->s = 0;
    c->c = 0;
    c->ch[0] = 0;
    while (l) {
        if (c->p) {
            free(c->p);
            c->p = 0;
        }
        while (l && l--) {
            c->ch[0] += c->ch[l + 1];
        }
        if (l) {
            c->p = (char *)malloc(l);
            assert(c->p);
            for (i = 0; i < l; i++) {
                c->p[i] = p->ch[i + 1];
            }
        } else {
            c->s = c->c + c->ch[0];
        }
    }
    return 0;
}