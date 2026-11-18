void __cdecl SetBpfStringFromFile(char *filename)
{
  int v1; // eax
  char *v2; // rax
  char *v3; // [rsp+0h] [rbp-E0h]
  char *v4; // [rsp+8h] [rbp-D8h]
  bool v5; // [rsp+16h] [rbp-CAh]
  bool v6; // [rsp+17h] [rbp-C9h]
  size_t nm; // [rsp+18h] [rbp-C8h]
  FILE *fp; // [rsp+20h] [rbp-C0h]
  SCStat st; // [rsp+28h] [rbp-B8h] BYREF
  uint32_t bpf_len; // [rsp+BCh] [rbp-24h]
  char *bpf_comment_start; // [rsp+C0h] [rbp-20h]
  char *bpf_comment_tmp; // [rsp+C8h] [rbp-18h]
  char *bpf_filter; // [rsp+D0h] [rbp-10h]
  char *filenamea; // [rsp+D8h] [rbp-8h]

  filenamea = filename;
  bpf_filter = 0LL;
  bpf_comment_tmp = 0LL;
  bpf_comment_start = 0LL;
  bpf_len = 0;
  fp = fopen(filename, "r");
  if ( !fp )
  {
    vb_log_stub("Failed to open file %s", filenamea);
    exit(1);
  }
  v1 = fileno(fp);
  if ( fstat(v1, &st) )
  {
    vb_log_stub("Failed to stat file %s", filenamea);
    exit(1);
  }
  bpf_len = LODWORD(st.st_size) + 1;
  bpf_filter = (char *)calloc(1uLL, (unsigned int)(LODWORD(st.st_size) + 1));
  if ( !bpf_filter )
  {
    vb_log_stub("Failed to allocate buffer for bpf filter in file %s", filenamea);
    exit(1);
  }
  nm = fread(bpf_filter, 1uLL, bpf_len - 1, fp);
  if ( ferror(fp) || nm != bpf_len - 1 )
  {
    vb_log_stub("Failed to read complete BPF file %s", filenamea);
    free(bpf_filter);
    fclose(fp);
    exit(1);
  }
  fclose(fp);
  bpf_filter[nm] = 0;
  if ( strlen(bpf_filter) )
  {
    for ( bpf_comment_start = bpf_filter; ; bpf_comment_start = bpf_comment_tmp )
    {
      bpf_comment_tmp = strchr(bpf_comment_start, 35);
      if ( !bpf_comment_tmp )
        break;
      while ( 1 )
      {
        v6 = 0;
        if ( *bpf_comment_tmp )
        {
          v6 = 0;
          if ( *bpf_comment_tmp != 13 )
            v6 = *bpf_comment_tmp != 10;
        }
        if ( !v6 )
          break;
        v2 = bpf_comment_tmp++;
        *v2 = 32;
      }
    }
    while ( 1 )
    {
      bpf_comment_tmp = strchr(bpf_filter, 13);
      if ( !bpf_comment_tmp )
        break;
      *bpf_comment_tmp = 32;
    }
    while ( 1 )
    {
      bpf_comment_tmp = strchr(bpf_filter, 10);
      if ( !bpf_comment_tmp )
        break;
      *bpf_comment_tmp = 32;
    }
    while ( 1 )
    {
      v5 = 0;
      if ( strlen(bpf_filter) )
      {
        v4 = bpf_filter;
        v5 = v4[strlen(bpf_filter) - 1] == 32;
      }
      if ( !v5 )
        break;
      v3 = bpf_filter;
      v3[strlen(bpf_filter) - 1] = 0;
    }
    if ( strlen(bpf_filter) && ConfSetFinal("bpf-filter", bpf_filter) != 1 )
    {
      free(bpf_filter);
      vb_log_stub("failed to set bpf filter");
      exit(1);
    }
  }
  free(bpf_filter);
}