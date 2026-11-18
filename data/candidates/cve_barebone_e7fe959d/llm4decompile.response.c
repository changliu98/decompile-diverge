int bgzf_index_load_hfile(BGZF *fp, hFILE *idx, const char *fn)
{
    int i;
    fp->idx = calloc(1, sizeof(bgzidx_t));
    if (fp->idx == 0) goto error;
    uint64_t n_gzip;
    if (hread_uint64(&n_gzip, idx) < 0) goto error;
    fp->idx->moffs = fp->idx->noffs = n_gzip + 1;
    fp->idx->offs = malloc(fp->idx->moffs * sizeof(bgzidx1_t));
    if (fp->idx->offs == 0) goto error;
    fp->idx->offs[0].caddr = fp->idx->offs[0].uaddr = 0;
    for (i = 1; i < fp->idx->noffs; ++i) {
        if (hread_uint64(&fp->idx->offs[i].caddr, idx) < 0) goto error;
        if (hread_uint64(&fp->idx->offs[i].uaddr, idx) < 0) goto error;
    }
    return 0;

error:
    hts_log_error("Error reading %s : %s", fn?fn:"index", strerror(*__errno_location()));
    if (fp->idx) {
        free(fp->idx->offs);
        free(fp->idx);
        fp->idx = 0;
    }
    return -1;
}