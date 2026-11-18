int bgzf_index_load_hfile(struct s_node **c, char *s, FILE *fp) {
    int i;
    struct s_node *t;

    while (1) {
        *c = (struct s_node *)calloc(1, sizeof(struct s_node));
        if (*c == NULL)
            return -1;
        if (getword(&((*c)->s), s) < 0)
            break;
        (*c)->left = (*c)->right = NULL;
        for (i = 1; i < (*c)->k; i++)
            if (getword(&((*c)->c[i].s), s) < 0 ||
                getint(&((*c)->c[i].n), s) < 0)
                break;
        if (i == (*c)->k)
            continue;
        t = *c;
        *c = (*c)->left;
        free(t);
    }
    if (fp!= NULL)
        fclose(fp);
    return 0;
}