int __cdecl bgzf_index_load_hfile(BGZF *fp, hFILE *idx, const char *name)
{
  int v3; // ecx
  int *v4; // rax
  char *v5; // rax
  const char *v7; // [rsp+8h] [rbp-38h]
  int i; // [rsp+14h] [rbp-2Ch]
  uint64_t x; // [rsp+18h] [rbp-28h] BYREF
  const char *namea; // [rsp+20h] [rbp-20h]
  hFILE *idxa; // [rsp+28h] [rbp-18h]
  BGZF *fpa; // [rsp+30h] [rbp-10h]

  fpa = fp;
  idxa = idx;
  namea = name;
  fp->idx = (bgzidx_t *)calloc(1uLL, 0x18uLL);
  if ( fpa->idx
    && hread_uint64(&x, idxa) >= 0
    && (v3 = x + 1,
        fpa->idx->moffs = x + 1,
        fpa->idx->noffs = v3,
        (fpa->idx->offs = (bgzidx1_t *)malloc(16LL * fpa->idx->moffs)) != 0LL) )
  {
    fpa->idx->offs->uaddr = 0LL;
    fpa->idx->offs->caddr = 0LL;
    for ( i = 1; i < fpa->idx->noffs; ++i )
    {
      if ( hread_uint64(&fpa->idx->offs[i].caddr, idxa) < 0 || hread_uint64(&fpa->idx->offs[i].uaddr, idxa) < 0 )
        goto fail;
    }
    return 0;
  }
  else
  {
fail:
    if ( namea )
      v7 = namea;
    else
      v7 = "index";
    v4 = __errno_location();
    v5 = strerror(*v4);
    hts_log_error("Error reading %s : %s", v7, v5);
    if ( fpa->idx )
    {
      free(fpa->idx->offs);
      free(fpa->idx);
      fpa->idx = 0LL;
    }
    return -1;
  }
}