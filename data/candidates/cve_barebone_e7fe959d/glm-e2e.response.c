int bgzf_index_load_hfile(struct bgzf_file_t *fp, void *hfile, const char *name) {
    uint64_t count;
    int i;
    const char *msg;

    fp->index = calloc(1, 24);
    if (!fp->index) {
        goto fail;
    }

    if (hread_uint64(hfile, &count) < 0) {
        goto fail;
    }

    fp->index->m = count + 1;
    fp->index->n = count + 1;

    fp->index->entries = malloc((size_t)fp->index->m * 16);
    if (!fp->index->entries) {
        goto fail;
    }

    // Initialize the first entry to zero
    ((uint64_t *)fp->index->entries)[0] = 0;
    ((uint64_t *)fp->index->entries)[1] = 0;

    for (i = 1; i < fp->index->n; i++) {
        if (hread_uint64(hfile, (uint64_t *)fp->index->entries + i * 2 + 1) < 0) {
            goto fail;
        }
        if (hread_uint64(hfile, (uint64_t *)fp->index->entries + i * 2) < 0) {
            goto fail;
        }
    }

    return 0;

fail:
    msg = name ? name : "(unknown)";
    hts_log_error("Could not load BGZF index: %s", strerror(errno));
    
    if (fp->index) {
        free(fp->index->entries);
        free(fp->index);
        fp->index = NULL;
    }
    
    return -1;
}