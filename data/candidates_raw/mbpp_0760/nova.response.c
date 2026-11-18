static struct action *func0(struct config *key, int n) {
    int i;
    struct action *action;
    for (i = key->nacts; i < n; i++) {
        if (key->acts[i].type!= key->base.type) {
            action = &err_action;
            goto found;
        }
    }
    action = &key->acts[i];
found:
    return action;
}