int access_parse_oid(unsigned char *oid, unsigned long oidlen, char **group_name, unsigned long *group_namelen, char **context_prefix, unsigned long *context_prefixlen, int *model, int *level)
{
    int i;
    int group_name_len; int context_prefix_len;
    if (oidlen == 0 || oid == ((void *)0)) {
        return 1;
    }
    group_name_len = (int)oid[0];
    context_prefix_len = (int)oid[group_name_len + 1];
    if (oidlen != (unsigned long)(group_name_len +
                                 context_prefix_len +
                                 sizeof(int) * 2)) {
        return 1;
    }
    if (context_prefix == ((void *)0) || group_name == ((void *)0)) {
        return 1;
    }
    if ((*group_name = (char *)mbedtls_calloc(group_name_len + 1)) ==
        ((void *)0)) {
        return 1;
    }
    if ((*context_prefix = (char *)mbedtls_calloc(context_prefix_len + 1)) ==
        ((void *)0)) {
        mbedtls_free(*group_name);
        return 1;
    }
    *context_prefixlen = (unsigned long)context_prefix_len;
    *group_namelen = (unsigned long)group_name_len;
    for (i = 0; i < group_name_len; i++) {
        if (oid[i + 1] > 0xff) {
            mbedtls_free(*group_name);
            mbedtls_free(*context_prefix);
            return 1;
        }
        (*group_name)[i] = (char)oid[i + 1];
    }
    (*group_name)[group_name_len] = '\0';
    for (i = 0; i < context_prefix_len; i++) {
        if (oid[group_name_len + 1 + i] > 0xff) {
            mbedtls_free(*group_name);
            mbedtls_free(*context_prefix);
            return 1;
        }
        (*context_prefix)[i] = (char)oid[group_name_len + 1 + i];
    }
    (*context_prefix)[context_prefix_len] = '\0';
    *model = (int)oid[context_prefix_len + 1 + group_name_len];
    *level = (int)oid[context_prefix_len + 1 + group_name_len + 1];
    return 0;
}