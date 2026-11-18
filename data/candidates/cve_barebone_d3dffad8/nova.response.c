static struct tree *jp2_box_get(struct repository *r) {
    struct tree *t = NULL;
    struct tree *t2 = NULL;
    struct commit *c = NULL;
    struct commit *c2 = NULL;
    struct commit_list *parents;
    struct commit_list *parents2;

    while (1) {
        t = alloc_tree();
        if (!t)
            break;
        t->path = ".";
        if (get_tree_recursive(r, &t->object.oid))
            break;
        t->object.parsed = 1;
        if (t->object.oid.hash[0] & 1)
            break;
        c = alloc_commit();
        if (!c)
            break;
        if (get_commit_tree(c, r))
            break;
        t->object.oid = c->tree->object.oid;
        t->object.parsed = 1;
        if (t->object.oid.hash[0] & 1)
            break;
        c2 = c;
        c = NULL;
    }
    while (1) {
        if (!t)
            break;
        if (t->object.parsed)
            break;
        free_tree(t);
        if (!c2)
            break;
        t = c2->tree;
        c2 = NULL;
    }
    if (t)
        free_tree(t);
    if (c2)
        free_commit(c2);
    return c2;
}