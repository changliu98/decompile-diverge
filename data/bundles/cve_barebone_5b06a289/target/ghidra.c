void SetBpfStringFromFile(char *filename)

{
  int iVar1;
  FILE *__stream;
  char *__s;
  size_t sVar2;
  char *pcVar3;
  bool bVar4;
  size_t nm;
  FILE *fp;
  SCStat st;
  uint32_t bpf_len;
  char *bpf_comment_start;
  char *bpf_comment_tmp;
  char *bpf_filter;
  char *filename_local;
  
  __stream = fopen(filename,"r");
  if (__stream == (FILE *)0x0) {
    vb_log_stub("Failed to open file %s",filename);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  iVar1 = fileno(__stream);
  iVar1 = fstat(iVar1,(stat *)&st);
  if (iVar1 != 0) {
    vb_log_stub("Failed to stat file %s",filename);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  __s = calloc(1,(ulong)((uint)st.st_size + 1));
  if (__s == (char *)0x0) {
    vb_log_stub("Failed to allocate buffer for bpf filter in file %s",filename);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  sVar2 = fread(__s,1,(ulong)(uint)st.st_size,__stream);
  iVar1 = ferror(__stream);
  if ((iVar1 == 0) && (sVar2 == (uint)st.st_size)) {
    fclose(__stream);
    __s[sVar2] = '\0';
    sVar2 = strlen(__s);
    bpf_comment_start = __s;
    if (sVar2 != 0) {
      while (bpf_comment_tmp = strchr(bpf_comment_start,0x23), bpf_comment_tmp != (char *)0x0) {
        while( true ) {
          bVar4 = false;
          if ((*bpf_comment_tmp != '\0') && (bVar4 = false, *bpf_comment_tmp != '\r')) {
            bVar4 = *bpf_comment_tmp != '\n';
          }
          if (!bVar4) break;
          *bpf_comment_tmp = ' ';
          bpf_comment_tmp = bpf_comment_tmp + 1;
        }
        bpf_comment_start = bpf_comment_tmp;
      }
      while (pcVar3 = strchr(__s,0xd), pcVar3 != (char *)0x0) {
        *pcVar3 = ' ';
      }
      while (pcVar3 = strchr(__s,10), pcVar3 != (char *)0x0) {
        *pcVar3 = ' ';
      }
      while( true ) {
        sVar2 = strlen(__s);
        bVar4 = false;
        if (sVar2 != 0) {
          sVar2 = strlen(__s);
          bVar4 = __s[sVar2 - 1] == ' ';
        }
        if (!bVar4) break;
        sVar2 = strlen(__s);
        __s[sVar2 - 1] = '\0';
      }
      sVar2 = strlen(__s);
      if ((sVar2 != 0) && (iVar1 = ConfSetFinal("bpf-filter",__s), iVar1 != 1)) {
        free(__s);
        vb_log_stub("failed to set bpf filter");
                    /* WARNING: Subroutine does not return */
        exit(1);
      }
    }
    free(__s);
    return;
  }
  vb_log_stub("Failed to read complete BPF file %s",filename);
  free(__s);
  fclose(__stream);
                    /* WARNING: Subroutine does not return */
  exit(1);
}