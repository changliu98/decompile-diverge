void ezxml_char_content(ezxml_root_t root, char *s, size_t len, char nl)
{
    ezxml_node_t n = root->cur;
    char *t, *b = s;

    if (! n || ! n->name || ! len) return;
    s[len] = '\0';
    s = ezxml_decode(s, root->s, nl);

    len = strlen(s) + 1;
    if (*n->txt == '\0') {
        n->txt = s;
    }
    else if (n->flags & (1 << 6)) {
        t = n->txt;
        n->txt = (char *)realloc(t, strlen(n->txt) + len);
        strcpy(n->txt + strlen(t), s);
        if (s != b) free(s);
    }
    else {
        n->txt = (char *)malloc(strlen(n->txt) + len);
        n->txt = strcpy(n->txt, n->txt);
        strcat(n->txt, s);
        if (s != b) free(s);
    }

    if (n->txt != b) ezxml_set_flag(n, (1 << 6));
}