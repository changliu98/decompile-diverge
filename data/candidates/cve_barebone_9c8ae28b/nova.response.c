void messageAddArgument(struct config *cfp, char *var) {
    int i;
    char *val;
    struct config *newcfp;

    assert(cfp);
    assert(var);
    assert(strcmp(var, "=")!= 0);
    for (;;) {
        if (isspace(*var))
            var++;
        else
            break;
    }
    if (*var == 0)
        return;
    for (;;) {
        if (isspace(*var))
            var++;
        else
            break;
    }
    if (*var == 0)
        return;
    for (;;) {
        if (isspace(*var))
            var++;
        else
            break;
    }
    if (*var == 0)
        return;
    if (strncmp(var, "=", 1) == 0) {
        var++;
        *var = '=';
    }
    val = var;
    for (;;) {
        if (*var == 0)
            break;
        if (strchr(var, '=')) {
            free(val);
            val = NULL;
            break;
        }
        var++;
    }
    for (i = 0; i < cfp->nval; i++)
        if (strcmp(cfp->val[i], val) == 0) {
            free(val);
            cfp->val[i] = NULL;
            break;
        }
    if (i == cfp->nval) {
        newcfp = install(val);
        append(newcfp, cfp);
    }
    return;
}