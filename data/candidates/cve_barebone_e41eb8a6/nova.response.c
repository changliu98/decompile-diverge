int access_parse_oid(const uint8_t *data, size_t data_len, char **name,
                    size_t *name_len, char **value, size_t *value_len) {
    int i;
    int is_first;

    if (data_len <= 0 || data == NULL) {
        is_first = 1;
    } else {
        int start = (int)data[0];
        int end = (int)data[start + 1];

        while (1) {
            if (start + end + 4 > data_len) {
                is_first = 1;
                break;
            }

            if (value == NULL || name == NULL) {
                is_first = 1;
                break;
            }

            *name = (char *)malloc(start + 1);
            if (*name == NULL) {
                is_first = 1;
                break;
            }

            *value = (char *)malloc(end + 1);
            if (*value == NULL) {
                free(*name);
                is_first = 1;
                break;
            }

            for (i = 0; i < start; i++) {
                (*name)[i] = data[i + 1];
            }
            (*name)[i] = '\0';

            for (i = 0; i < end; i++) {
                (*value)[i] = data[start + i + 2];
            }
            (*value)[i] = '\0';

            *name_len = start;
            *value_len = end;

            is_first = 0;
            break;
        }
    }

    return is_first;
}