int mbedtls_oid_get_from_asn1(unsigned char *oid, unsigned long len, char **group_name, unsigned long *group_name_len, char **context_prefix, unsigned long *context_prefix_len, int *model, int *level)
{
    int i; int group_name_len_int; int context_prefix_len_int;
    if (len == 0 || oid == ((void *)0)) {
        return 1;
    }
    group_name_len_int = (int)oid[0];
    context_prefix_len_int = (int)oid[group_name_len_int + 1];
    if (len != (unsigned long)(group_name_len_int + context_prefix_len_int +
                             sizeof(int) * 2)) {
        return 1;
    }
    if (context_prefix == ((void *)0) || group_name == ((void *)0)) {
        return 1;
    }
    if ((*group_name = (char *)mbedtls_calloc(group_name_len_int + 1)) == ((void *)0)) {
        return 1;
    }
    if ((*context_prefix = (char *)mbedtls_calloc(context_prefix_len_int + 1)) == ((void *)0)) {
        mbedtls_free(*group_name);
        return 1;
    }
    *context_prefix_len = context_prefix_len_int;
    *group_name_len = group_name_len_int;
    for (i = 0; i < group_name_len_int; i++) {
        if (oid[i + 1] > 0xff) {
            mbedtls_free(*group_name);
            mbedtls_free(*context_prefix);
            return 1;
        }
        (*group_name)[i] = (char)oid[i + 1];
    }
    (*group_name)[group_name_len_int] = '\0';
    for (i = 0; i < context_prefix_len_int; i++) {
        if (oid[group_name_len_int + i + 2] > 0xff) {
            mbedtls_free(*group_name);
            mbedtls_free(*context_prefix);
            return 1;
        }
        (*context_prefix)[i] = (char)oid[group_name_len_int + i + 2];
    }
    (*context_prefix)[context_prefix_len_int] = '\0';
    *model = (int)oid[context_prefix_len_int + group_name_len_int + 2];
    *level = (int)oid[context_prefix_len_int + group_name_len_int + 3];
    return 0;
}