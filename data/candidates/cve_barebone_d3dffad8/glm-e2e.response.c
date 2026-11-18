struct jp2_box *jp2_box_get(void *in) {
    struct jp2_box *box = NULL;
    void *tmpstream = NULL;
    uint32_t type;
    uint64_t length;

    box = jas_malloc(0x140);
    if (!box) {
        goto cleanup;
    }

    box->ops = (struct jp2_box_ops *)((char *)&jp2_boxinfo_unk + 0x18);

    if (jp2_getuint32(in, &type) || jp2_getuint32(in, &box->type)) {
        goto cleanup;
    }

    box->info = jp2_boxinfolookup(box->type);
    box->ops = (struct jp2_box_ops *)((char *)box->info + 0x18);
    box->len = type;

    if (jas_getdbglevel() >= 10) {
        jas_eprintf("box type: %s (0x%x); length: %llu\n", 
                    box->info->dummy1, box->type, box->len);
    }

    if (box->len == 1) {
        if (jp2_getuint64(in, &length)) {
            goto cleanup;
        }
        if (length > 0xffffffffULL) {
            jas_eprintf("box length too large\n");
            length = 0xffffffffULL;
        }
        box->len = length;
        box->data_len = length - 16;
    } else {
        box->data_len = box->len - 8;
    }

    if (box->len != 0 && box->len < 8) {
        goto cleanup;
    }

    if ((box->info->flags & 0x3) == 0) {
        tmpstream = jas_stream_memopen(0, 0);
        if (!tmpstream) {
            goto cleanup;
        }

        if (jas_stream_copy(tmpstream, in, (uint32_t)box->data_len)) {
            box->ops = (struct jp2_box_ops *)((char *)&jp2_boxinfo_unk + 0x18);
            jas_eprintf("cannot copy box data\n");
            goto cleanup;
        }

        jas_stream_rewind(tmpstream);

        if (box->ops->getdata) {
            if (box->ops->getdata(box, tmpstream)) {
                jas_eprintf("error in box getdata\n");
                goto cleanup;
            }
        }

        jas_stream_close(tmpstream);
        tmpstream = NULL;
    }

    if (jas_getdbglevel() >= 1) {
        jp2_box_dump(box, stderr);
    }

    return box;

cleanup:
    if (box) {
        jp2_box_destroy(box);
    }
    if (tmpstream) {
        jas_stream_close(tmpstream);
    }
    return NULL;
}