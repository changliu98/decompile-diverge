char *mfile_name_concat(char *arg1, char *arg2, char **arg3) {
    char *var28 = last_component(arg1);
    size_t var30 = base_len(var28);
    size_t var38 = (var28 - arg1) + var30;
    size_t var40 = strlen(arg2);
    char var41 = 0;

    if (var30 != 0) {
        if (arg1[var38 - 1] != '/' && arg2[0] != '/') {
            var41 = '/';
        }
    } else {
        if (arg2[0] == '/') {
            var41 = '.';
        }
    }

    size_t total_size = var38 + (var41 != 0 ? 1 : 0) + var40 + 1;
    char *var50 = malloc(total_size);
    if (var50 == NULL) {
        return NULL;
    }

    char *var58 = var50;
    memcpy(var58, arg1, var38);
    var58 += var38;

    if (var41 != 0) {
        *var58 = var41;
        var58++;
    }

    if (arg3 != NULL) {
        *arg3 = var58;
    }

    char *var68 = var58;
    memcpy(var68, arg2, var40);
    var58 += var40;
    *var58 = '\0';

    return var50;
}