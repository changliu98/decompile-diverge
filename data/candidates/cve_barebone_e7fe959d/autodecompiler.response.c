static int bgzf_index_load_hfile(BAI2 *idx, BGZF *fp, char *filename) {
    int ret;
    uint64_t n;

    idx->bpl = (BAI2_BPT*)calloc(1, sizeof(BAI2_BPT));
    if (!idx->bpl)
        goto fail;

    if (hread_uint64(&n, fp) < 0)
        goto fail;

    idx->bpl->n = idx->bpl->m = n + 1;
    idx->bpl->offsets = (BAI2_BPOff*)malloc(idx->bpl->m * sizeof(BAI2_BPOff));
    if (!idx->bpl->offsets)
        goto fail;

    idx->bpl->offsets[0].tid = 0;
    idx->bpl->offsets[0].off = 0;

    for (int i = 1; ; ++i) {
        if (i < idx->bpl->m) {
            if (hread_uint64(&idx->bpl->offsets[i].tid, fp) < 0)
                goto fail;
            if (hread_uint64(&idx->bpl->offsets[i].off, fp) < 0)
                goto fail;
        } else {
            break;
        }
    }

    ret = 0;
    while (ret >= 0) {
        uint64_t tid, off, bin, n_mapped, n_unmapped;
        if (hread_uint64(&tid, fp) < 0)
            break;
        if (hread_uint64(&off, fp) < 0)
            goto fail;
        if (hread_uint64(&bin, fp) < 0)
            goto fail;
        if (hread_uint64(&n_mapped, fp) < 0)
            goto fail;
        if (hread_uint64(&n_unmapped, fp) < 0)
            goto fail;

        if (tid == 0xffffffffffffffffU) {
            if (bin == 0xffffffffU) {

                if (n_mapped != 0xffffffffU || n_unmapped != 0xffffffffU)
                    goto fail;

                if (idx->bpl->n < idx->bpl->m) {
                    idx->bpl->n = idx->bpl->m;
                    idx->bpl->offsets = (BAI2_BPOff*)realloc(idx->bpl->offsets,
                                                              idx->bpl->m * sizeof(BAI2_BPOff));
                    if (!idx->bpl->offsets)
                        goto fail;
                }
                idx->bpl->offsets[idx->bpl->n].tid = tid;
                idx->bpl->offsets[idx->bpl->n].off = off;
                ++idx->bpl->n;
            } else {

                BAI2_CSI_CHROM *c = csi_chrom_find(idx, tid);
                if (c) {
                    c->bins.n = c->bins.m = n_mapped + 1;
                    c->bins.offsets = (uint64_t*)malloc(c->bins.m * sizeof(uint64_t));
                    if (!c->bins.offsets)
                        goto fail;
                    c->bins.offsets[0] = 0;
                    for (int j = 1; j < c->bins.n; ++j) {
                        if (hread_uint64(&c->bins.offsets[j], fp) < 0)
                            goto fail;
                    }
                }
            }
        } else {

            BAI2_CSI_CHROM *c = csi_chrom_find(idx, tid);
            if (c) {
                c->bins.n = c->bins.m = n_mapped + 1;
                c->bins.offsets = (uint64_t*)malloc(c->bins.m * sizeof(uint64_t));
                if (!c->bins.offsets)
                    goto fail;
                c->bins.offsets[0] = 0;
                for (int j = 1; j < c->bins.n; ++j) {
                    if (hread_uint64(&c->bins.offsets[j], fp) < 0)
                        goto fail;
                }
            }
        }
    }

    return ret;

fail:
    do { hts_log_error("Error reading %s : %s", filename? filename : "index", strerror(*___errno_location())); } while (0);
    if (idx->bpl) {
        free(idx->bpl->offsets);
        free(idx->bpl);
        idx->bpl = NULL;
    }
    return -1;
}