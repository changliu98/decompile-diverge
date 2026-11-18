int abst_box_read(abst_box *box, void *bs) {
    int ret = GF_OK;
    char *str_buf = NULL;

    if (box->size < 25) {
        return GF_ISOM_INVALID_FILE;
    }
    box->size -= 25;

    box->field_0x28 = gf_bs_read_u32(bs);
    box->field_0x2c = gf_bs_read_int(bs, 2);
    box->field_0x30 = gf_bs_read_int(bs, 1);
    box->field_0x34 = gf_bs_read_int(bs, 1);
    box->field_0x38 = gf_bs_read_int(bs, 4);
    box->field_0x3c = gf_bs_read_u32(bs);
    box->field_0x40 = gf_bs_read_u64(bs);
    box->field_0x48 = gf_bs_read_u64(bs);

    int str_len = 0;
    if (box->size < 8) {
        return GF_ISOM_INVALID_FILE;
    }
    uint32_t alloc_size = (uint32_t)box->size;
    str_buf = (char *)gf_malloc(alloc_size);
    if (!str_buf) {
        return GF_OUT_OF_MEM;
    }
    memset(str_buf, 0, alloc_size);

    while (alloc_size != 0) {
        if (box->size < 1) {
            ret = GF_ISOM_INVALID_FILE;
            goto cleanup;
        }
        box->size -= 1;
        str_buf[str_len] = gf_bs_read_u8(bs);
        alloc_size--;
        if (str_buf[str_len] == 0) {
            break;
        }
        str_len++;
    }

    if (str_len != 0) {
        box->field_0x50 = gf_strdup(str_buf);
    }

    if (box->size < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    box->size -= 1;
    box->field_0x58 = gf_bs_read_u8(bs);

    for (int i = 0; i < box->field_0x58; i++) {
        int len = 0;
        uint32_t rem_size = (uint32_t)box->size;
        while (rem_size != 0) {
            if (box->size < 1) {
                ret = GF_ISOM_INVALID_FILE;
                goto cleanup;
            }
            box->size -= 1;
            str_buf[len] = gf_bs_read_u8(bs);
            rem_size--;
            if (str_buf[len] == 0) {
                break;
            }
            len++;
        }
        if (len != 0) {
            void *list = box->field_0x60;
            char *new_str = gf_strdup(str_buf);
            gf_list_insert(list, new_str, i);
        }
    }

    if (box->size < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    box->size -= 1;
    box->field_0x68 = gf_bs_read_u8(bs);

    for (int i = 0; i < box->field_0x68; i++) {
        int len = 0;
        uint32_t rem_size = (uint32_t)box->size;
        while (rem_size != 0) {
            if (box->size < 1) {
                ret = GF_ISOM_INVALID_FILE;
                goto cleanup;
            }
            box->size -= 1;
            str_buf[len] = gf_bs_read_u8(bs);
            rem_size--;
            if (str_buf[len] == 0) {
                break;
            }
            len++;
        }
        if (len != 0) {
            void *list = box->field_0x70;
            char *new_str = gf_strdup(str_buf);
            gf_list_insert(list, new_str, i);
        }
    }

    str_len = 0;
    uint32_t rem_size = (uint32_t)box->size;
    while (rem_size != 0) {
        if (box->size < 1) {
            ret = GF_ISOM_INVALID_FILE;
            goto cleanup;
        }
        box->size -= 1;
        str_buf[str_len] = gf_bs_read_u8(bs);
        rem_size--;
        if (str_buf[str_len] == 0) {
            break;
        }
        str_len++;
    }
    if (str_len != 0) {
        box->field_0x78 = gf_strdup(str_buf);
    }

    str_len = 0;
    rem_size = (uint32_t)box->size;
    while (rem_size != 0) {
        if (box->size < 1) {
            ret = GF_ISOM_INVALID_FILE;
            goto cleanup;
        }
        box->size -= 1;
        str_buf[str_len] = gf_bs_read_u8(bs);
        rem_size--;
        if (str_buf[str_len] == 0) {
            break;
        }
        str_len++;
    }
    if (str_len != 0) {
        box->field_0x80 = gf_strdup(str_buf);
    }

    if (box->size < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    box->size -= 1;
    box->field_0x88 = gf_bs_read_u8(bs);

    for (int i = 0; i < box->field_0x88; i++) {
        void *child_a = NULL;
        int e = gf_isom_box_parse(&child_a, bs);
        if (e) {
            if (child_a) {
                gf_isom_box_del(child_a);
            }
            ret = e;
            goto cleanup;
        }
        gf_list_add(box->field_0x90, child_a);
    }

    if (box->size < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    box->size -= 1;
    box->field_0x98 = gf_bs_read_u8(bs);

    for (int i = 0; i < box->field_0x98; i++) {
        void *child_b = NULL;
        int e = gf_isom_box_parse(&child_b, bs);
        if (e) {
            if (child_b) {
                gf_isom_box_del(child_b);
            }
            ret = e;
            goto cleanup;
        }
        gf_list_add(box->field_0xa0, child_b);
    }

cleanup:
    gf_free(str_buf);
    return ret;
}