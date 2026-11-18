ComplexObject *get_complex_object(uint32_t *arg1, RzBuffer *arg2) {
    ComplexObject *obj = NULL;
    bool error = false;
    int read_len = 0;
    int32_t len1 = 0;
    int32_t len2 = 0;
    char *buf1 = NULL;
    char *buf2 = NULL;

    obj = calloc(1, 16);
    if (!obj) {
        return NULL;
    }

    if ((*arg1 & 0xffff) <= 0xf26d) {
        len1 = get_ut8(arg2, &error);
    } else {
        len1 = get_st32(arg2, &error);
    }

    if (error) {
        free(obj);
        return NULL;
    }

    buf1 = malloc(len1 + 1);
    if (!buf1) {
        return NULL;
    }

    read_len = rz_buf_read(arg2, buf1, len1);
    if (read_len != len1) {
        free(buf1);
        free(obj);
        return NULL;
    }
    buf1[len1] = '\0';

    if ((*arg1 & 0xffff) <= 0xf26d) {
        len2 = get_ut8(arg2, &error);
    } else {
        len2 = get_st32(arg2, &error);
    }

    if (error) {
        return NULL;
    }

    buf2 = malloc(len2 + 1);
    if (!buf2) {
        return NULL;
    }

    read_len = rz_buf_read(arg2, buf2, len2);
    if (read_len != len2) {
        free(buf1);
        free(buf2);
        free(obj);
        return NULL;
    }
    buf2[len2] = '\0';

    obj->field1 = 0x78;
    obj->field2 = rz_str_newf("%s%s", buf1, buf2); // Format string inferred from 0x205e

    free(buf1);
    free(buf2);

    if (!obj->field2) {
        free(obj);
        return NULL;
    }

    return obj;
}