int abst_box_read(abst_box *s, GF_BitStream *bs) {
    int ret = GF_OK;
    char *buf = NULL;
    int i, j;
    uint32_t buf_size;
    int str_len;
    GF_Box *a;

    if (s->remaining < 25) {
        return GF_ISOM_INVALID_FILE;
    }
    s->remaining -= 25;

    s->field_0x28 = gf_bs_read_u32(bs);
    s->field_0x2c = (uint8_t)gf_bs_read_int(bs, 2);
    s->field_0x30 = (uint8_t)gf_bs_read_int(bs, 1);
    s->field_0x34 = (uint8_t)gf_bs_read_int(bs, 1);
    s->field_0x38 = (uint8_t)gf_bs_read_int(bs, 4);
    s->field_0x3c = gf_bs_read_u32(bs);
    s->field_0x40 = gf_bs_read_u64(bs);
    s->field_0x48 = gf_bs_read_u64(bs);

    i = 0;
    if (s->remaining < 8) {
        return GF_ISOM_INVALID_FILE;
    }
    buf_size = (uint32_t)s->remaining - 8;
    buf = (char *)gf_malloc(buf_size);
    if (!buf) {
        return GF_OUT_OF_MEM;
    }
    memset(buf, 0, buf_size);

    while (buf_size != 0) {
        if (s->remaining < 1) {
            ret = GF_ISOM_INVALID_FILE;
            goto cleanup;
        }
        s->remaining -= 1;
        buf[i] = gf_bs_read_u8(bs);
        buf_size--;
        if (buf[i] == 0) {
            break;
        }
        i++;
    }

    if (i != 0) {
        s->field_0x50 = gf_strdup(buf);
    }

    if (s->remaining < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    s->remaining -= 1;
    s->field_0x58 = gf_bs_read_u8(bs);

    for (i = 0; i < s->field_0x58; i++) {
        j = 0;
        buf_size = (uint32_t)s->remaining;
        while (buf_size != 0) {
            if (s->remaining < 1) {
                ret = GF_ISOM_INVALID_FILE;
                goto cleanup;
            }
            s->remaining -= 1;
            buf[j] = gf_bs_read_u8(bs);
            buf_size--;
            if (buf[j] == 0) {
                break;
            }
            j++;
        }
        if (j != 0) {
            gf_list_insert(s->field_0x60, gf_strdup(buf), i);
        }
    }

    if (s->remaining < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    s->remaining -= 1;
    s->field_0x68 = gf_bs_read_u8(bs);

    for (i = 0; i < s->field_0x68; i++) {
        j = 0;
        buf_size = (uint32_t)s->remaining;
        while (buf_size != 0) {
            if (s->remaining < 1) {
                ret = GF_ISOM_INVALID_FILE;
                goto cleanup;
            }
            s->remaining -= 1;
            buf[j] = gf_bs_read_u8(bs);
            buf_size--;
            if (buf[j] == 0) {
                break;
            }
            j++;
        }
        if (j != 0) {
            gf_list_insert(s->field_0x70, gf_strdup(buf), i);
        }
    }

    i = 0;
    buf_size = (uint32_t)s->remaining;
    while (buf_size != 0) {
        if (s->remaining < 1) {
            ret = GF_ISOM_INVALID_FILE;
            goto cleanup;
        }
        s->remaining -= 1;
        buf[i] = gf_bs_read_u8(bs);
        buf_size--;
        if (buf[i] == 0) {
            break;
        }
        i++;
    }
    if (i != 0) {
        s->field_0x78 = gf_strdup(buf);
    }

    i = 0;
    buf_size = (uint32_t)s->remaining;
    while (buf_size != 0) {
        if (s->remaining < 1) {
            ret = GF_ISOM_INVALID_FILE;
            goto cleanup;
        }
        s->remaining -= 1;
        buf[i] = gf_bs_read_u8(bs);
        buf_size--;
        if (buf[i] == 0) {
            break;
        }
        i++;
    }
    if (i != 0) {
        s->field_0x80 = gf_strdup(buf);
    }

    if (s->remaining < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    s->remaining -= 1;
    s->field_0x88 = gf_bs_read_u8(bs);

    for (i = 0; i < s->field_0x88; i++) {
        a = NULL;
        ret = gf_isom_box_parse(&a, bs);
        if (ret != GF_OK) {
            if (a) {
                gf_isom_box_del(a);
            }
            goto cleanup;
        }
        gf_list_add(s->field_0x90, a);
    }

    if (s->remaining < 1) {
        ret = GF_ISOM_INVALID_FILE;
        goto cleanup;
    }
    s->remaining -= 1;
    s->field_0x98 = gf_bs_read_u8(bs);

    for (i = 0; i < s->field_0x98; i++) {
        a = NULL;
        ret = gf_isom_box_parse(&a, bs);
        if (ret != GF_OK) {
            if (a) {
                gf_isom_box_del(a);
            }
            goto cleanup;
        }
        gf_list_add(s->field_0xa0, a);
    }

    ret = GF_OK;

cleanup:
    gf_free(buf);
    return ret;
}