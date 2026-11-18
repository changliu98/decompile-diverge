int bgzf_read_index(struct bgzf *bgzf, struct hFILE *index, char *name)
{
  unsigned long n;
  int i;
  bgzf->idx = (struct bgzidx *)bgzf_alloc(1, sizeof(struct bgzidx));
  if (bgzf->idx == ((void *)0))
    goto fail;
  if (bgzf_read_long(&n, index) < 0)
    goto fail;
  bgzf->idx->moffs = n + 1;
  bgzf->idx->noffs = n + 1;
  bgzf->idx->offs = (struct bgzidx1 *)bgzf_alloc((unsigned long)(bgzf->idx->moffs), sizeof(struct bgzidx1));
  if (bgzf->idx->offs == ((void *)0))
    goto fail;
  bgzf->idx->offs->uaddr = 0;
  bgzf->idx->offs->caddr = 0;
  for (i = 1; i < bgzf->idx->noffs; i++) {
    if (bgzf_read_long(&bgzf->idx->offs[i].caddr, index) < 0)
      goto fail;
    if (bgzf_read_long(&bgzf->idx->offs[i].uaddr, index) < 0)
      goto fail;
  }
  return 0;
 fail:
  if (name == ((void *)0))
    name = "index";
  bgzf_fatal("Error reading %s : %s", name, bgzf_errstr(bgzf_errno()));
  if (bgzf->idx != ((void *)0)) {
    bgzf_free(bgzf->idx->offs);
    bgzf_free(bgzf->idx);
    bgzf->idx = ((void *)0);
  }
  return -1;
}