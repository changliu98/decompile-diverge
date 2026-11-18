void SetBpfStringFromFile(char *filename) {
  FILE *fp;
  struct stat st;
  char *bpf_filter = NULL;
  char *p = NULL;
  char *start = NULL;
  int size = 0;
  int ret;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    vb_log_stub("Failed to open file %s", filename);
    exit(1);
  }
  ret = fstat(fileno(fp), &st);
  if (ret != 0) {
    vb_log_stub("Failed to stat file %s", filename);
    exit(1);
  }
  size = st.st_size + 1;
  bpf_filter = calloc(1, size);
  if (bpf_filter == NULL) {
    vb_log_stub("Failed to allocate buffer for bpf filter in file %s",
                filename);
    exit(1);
  }
  ret = fread(bpf_filter, 1, size - 1, fp);
  if (ferror(fp) || ret != size - 1) {
    vb_log_stub("Failed to read complete BPF file %s", filename);
    free(bpf_filter);
    fclose(fp);
    exit(1);
  }
  fclose(fp);
  bpf_filter[ret] = '\0';
  if (strlen(bpf_filter) == 0) {
    free(bpf_filter);
    return;
  }
  start = bpf_filter;
  while ((p = strchr(start, '#')) != NULL) {
    while (*p != '\0' && *p != '\r' && *p != '\n') {
      *p++ = ' ';
    }
    start = p;
  }
  while ((p = strchr(bpf_filter, '\r')) != NULL) {
    *p = ' ';
  }
  while ((p = strchr(bpf_filter, '\n')) != NULL) {
    *p = ' ';
  }
  while (strlen(bpf_filter) > 0 && bpf_filter[strlen(bpf_filter) - 1] == ' ') {
    bpf_filter[strlen(bpf_filter) - 1] = '\0';
  }
  if (strlen(bpf_filter) > 0) {
    if (ConfSetFinal("bpf-filter", bpf_filter) != 1) {
      free(bpf_filter);
      vb_log_stub("failed to set bpf filter");
      exit(1);
    }
  }
  free(bpf_filter);
}