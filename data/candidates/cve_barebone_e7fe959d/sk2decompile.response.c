int bgzf_index_load_hfile(BGZF *fp, hFILE *hfp, const char *fn) {
  int i;
  uint64_t n_entries;
  fp->idx = (BGZF_Index *)calloc(1, sizeof(BGZF_Index));
  if (fp->idx == 0 || hread_uint64(&n_entries, hfp) < 0) goto fail;
  fp->idx->n_entries = n_entries + 1;
  fp->idx->max_pos = fp->idx->n_entries;
  fp->idx->entries =
      (BGZF_IndexEntry *)malloc(fp->idx->n_entries * sizeof(BGZF_IndexEntry));
  if (fp->idx->entries == 0) goto fail;
  fp->idx->entries[0].block_address = 0;
  fp->idx->entries[0].block_length = 0;
  for (i = 1; i < fp->idx->max_pos; i++) {
    if (hread_uint64(&fp->idx->entries[i].block_length, hfp) < 0 ||
        hread_uint64(&fp->idx->entries[i].block_address, hfp) < 0)
      goto fail;
  }
  return 0;
fail:
  hts_log_error("Error reading %s : %s", fn ? fn : "index", strerror(errno));
  if (fp->idx) {
    free(fp->idx->entries);
    free(fp->idx);
    fp->idx = 0;
  }
  return -1;
}