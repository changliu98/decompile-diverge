static char *cJSON_SetValuestring(struct config *conf, size_t len) {
    char *ret = NULL;
    if (!conf ||!((conf->mode & 0100) || (conf->mode & 001000))) {
        ret = NULL;
    } else if (!conf->value ||!len) {
        ret = NULL;
    } else {
        size_t val_len = strlen(conf->value);
        size_t conf_len = strlen(conf->value);
        if (val_len >= len) {
            if (conf->value + len >= conf->value && conf->value + len <= conf->value + conf_len) {
                ret = NULL;
            } else {
                memcpy(conf->value, len, conf->value);
                ret = conf->value;
            }
        } else {
            ret = realloc(conf->value, len + sizeof(char) - 1);
            if (!ret) {
                ret = NULL;
            } else if (conf->value) {
                free(conf->value);
            }
            conf->value = ret;
        }
    }
    return ret;
}