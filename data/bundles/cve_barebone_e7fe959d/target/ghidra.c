int bgzf_index_load_hfile(BGZF *fp,hFILE *idx,char *name)

{
  int iVar1;
  bgzidx_t *pbVar2;
  bgzidx1_t *pbVar3;
  int *piVar4;
  char *pcVar5;
  char *local_40;
  int i;
  uint64_t x;
  char *name_local;
  hFILE *idx_local;
  BGZF *fp_local;
  
  name_local = name;
  idx_local = idx;
  fp_local = fp;
  pbVar2 = calloc(1,0x18);
  fp_local->idx = pbVar2;
  if ((fp_local->idx != (bgzidx_t *)0x0) && (iVar1 = hread_uint64(&x,idx_local), -1 < iVar1)) {
    fp_local->idx->moffs = (int)x + 1;
    fp_local->idx->noffs = (int)x + 1;
    pbVar3 = malloc((long)fp_local->idx->moffs << 4);
    fp_local->idx->offs = pbVar3;
    if (fp_local->idx->offs != (bgzidx1_t *)0x0) {
      fp_local->idx->offs->uaddr = 0;
      fp_local->idx->offs->caddr = 0;
      i = 1;
      while( true ) {
        if (fp_local->idx->noffs <= i) {
          return 0;
        }
        iVar1 = hread_uint64(&fp_local->idx->offs[i].caddr,idx_local);
        if ((iVar1 < 0) ||
           (iVar1 = hread_uint64(&fp_local->idx->offs[i].uaddr,idx_local), iVar1 < 0)) break;
        i = i + 1;
      }
    }
  }
  if (name_local == (char *)0x0) {
    local_40 = "index";
  }
  else {
    local_40 = name_local;
  }
  piVar4 = __errno_location();
  pcVar5 = strerror(*piVar4);
  hts_log_error("Error reading %s : %s",local_40,pcVar5);
  if (fp_local->idx != (bgzidx_t *)0x0) {
    free(fp_local->idx->offs);
    free(fp_local->idx);
    fp_local->idx = (bgzidx_t *)0x0;
  }
  return -1;
}