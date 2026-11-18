void __cdecl SetBpfStringFromFile(char *filename)
{
  FILE *fp;
  SCStat st;
  uint32_t bpf_len;
  size_t bytes_read;
  char *bpf_filter;
  char *p;

  fp = fopen(filename, "r");
  if (!fp) {
    vb_log_stub("Failed to open file %s", filename);
    exit(1);
  }

  if (fstat(fileno(fp), &st)) {
    vb_log_stub("Failed to stat file %s", filename);
    exit(1);
  }

  bpf_len = LODWORD(st.st_size) + 1;
  bpf_filter = (char *)calloc(1uLL, bpf_len);
  if (!bpf_filter) {
    vb_log_stub("Failed to allocate buffer for bpf filter in file %s", filename);
    exit(1);
  }

  bytes_read = fread(bpf_filter, 1uLL, bpf_len - 1, fp);
  if (ferror(fp) || bytes_read != bpf_len - 1) {
    vb_log_stub("Failed to read complete BPF file %s", filename);
    free(bpf_filter);
    fclose(fp);
    exit(1);
  }
  fclose(fp);

  bpf_filter[bytes_read] = 0;

  if (strlen(bpf_filter)) {
    // Strip out comments: Replace everything from '#' to the end of the line with spaces
    p = bpf_filter;
    while ((p = strchr(p, '#')) != NULL) {
      while (*p && *p != '\r' && *p != '\n') {
        *p++ = ' ';
      }
    }

    // Replace all carriage returns with spaces
    while ((p = strchr(bpf_filter, '\r')) != NULL) {
      *p = ' ';
    }

    // Replace all newlines with spaces
    while ((p = strchr(bpf_filter, '\n')) != NULL) {
      *p = ' ';
    }

    // Trim trailing spaces
    while (strlen(bpf_filter) && bpf_filter[strlen(bpf_filter) - 1] == ' ') {
      bpf_filter[strlen(bpf_filter) - 1] = 0;
    }

    // Set the configuration if the string is not empty after stripping
    if (strlen(bpf_filter) && ConfSetFinal("bpf-filter", bpf_filter) != 1) {
      free(bpf_filter);
      vb_log_stub("failed to set bpf filter");
      exit(1);
    }
  }

  free(bpf_filter);
}