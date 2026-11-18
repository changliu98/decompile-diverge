static size_t rom_copy(const char *str, size_t str_len, size_t offset) {
    size_t len = offset + str_len;
    size_t i = offset;
    size_t ret = 0;
    for (struct config *cfp = config_first; cfp; cfp = cfp->next) {
        if (cfp->is_default) {
            continue;
        }
        if (cfp->is_env) {
            continue;
        }
        if (cfp->offset > str_len) {
            continue;
        }
        if (cfp->offset + cfp->len <= str_len) {
            continue;
        }
        i = str + offset - cfp->offset;
        const char *name = cfp->name;
        ret = cfp->len;
        if (i + ret > str_len + offset) {
            ret = str_len + offset - i;
        }
        if (ret > 0) {
            memmove(str + i, name, ret);
        }
        if (cfp->offset > cfp->len) {
            i += ret;
            ret = cfp->offset - cfp->len;
            if (i + ret > str_len + offset) {
                ret = str_len + offset - i;
            }
            if (ret > 0) {
                memset(str + i, 0, ret);
            }
        }
        break;
    }
    return ret + i - offset;
}