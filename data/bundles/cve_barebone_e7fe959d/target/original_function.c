int bgzf_index_load_hfile(BGZF *fp, struct hFILE *idx, const char *name)
{
    fp->idx = (bgzidx_t*) calloc(1,sizeof(bgzidx_t));
    if (fp->idx == NULL) goto fail;
    uint64_t x;
    if (hread_uint64(&x, idx) < 0) goto fail;

    fp->idx->noffs = fp->idx->moffs = x + 1;
    fp->idx->offs  = (bgzidx1_t*) malloc(fp->idx->moffs*sizeof(bgzidx1_t));
    if (fp->idx->offs == NULL) goto fail;
    fp->idx->offs[0].caddr = fp->idx->offs[0].uaddr = 0;

    int i;
    for (i=1; i<fp->idx->noffs; i++)
    {
        if (hread_uint64(&fp->idx->offs[i].caddr, idx) < 0) goto fail;
        if (hread_uint64(&fp->idx->offs[i].uaddr, idx) < 0) goto fail;
    }

    return 0;

 fail:
    hts_log_error("Error reading %s : %s", name ? name : "index", strerror(errno));
    if (fp->idx) {
        free(fp->idx->offs);
        free(fp->idx);
        fp->idx = NULL;
    }
    return -1;
}