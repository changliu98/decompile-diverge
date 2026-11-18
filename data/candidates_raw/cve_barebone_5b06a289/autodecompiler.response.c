static void load_bpf_filter(char *bpf_file)
{
 char *bpf_filter = NULL;
 char *bpf_comment_tmp = NULL;
 char *bpf_comment_start = NULL;
 unsigned int bpf_len = 0;
 struct stat st;
 FILE *f = NULL;
 size_t read = 0;

 f = fopen(bpf_file, "r");
 if (!f) {
  do { vb_log_stub("Failed to open file %s", bpf_file); } while(0);
  exit(1);
 }

 if (fstat(fileno(f), &st)) {
  do { vb_log_stub("Failed to stat file %s", bpf_file); } while(0);
  exit(1);
 }

 bpf_len = st.st_size + 1;

 bpf_filter = calloc(1, bpf_len);
 if (!((bpf_filter != NULL) ^ ((~0) & 1))) {
  do { vb_log_stub("Failed to allocate buffer for bpf filter in file %s", bpf_file); } while(0);
  exit(1);
 }

 read = fread(bpf_filter, 1, bpf_len - 1, f);

 if (ferror(f) || read != bpf_len - 1) {
  do { vb_log_stub("Failed to read complete BPF file %s", bpf_file); } while(0);
  free(bpf_filter);
  fclose(f);
  exit(1);
 }

 fclose(f);

 bpf_filter[read] = '\0';

 if (strlen(bpf_filter) > 0) {

  bpf_comment_start = bpf_filter;
  while ((bpf_comment_tmp = strchr(bpf_comment_start, '#'))) {
   while (*bpf_comment_tmp && *bpf_comment_tmp != '\r' && *bpf_comment_tmp != '\n')
    *bpf_comment_tmp++ = ' ';
   bpf_comment_start = bpf_comment_tmp;
  }


  while ((bpf_comment_tmp = strchr(bpf_filter, '\r')))
   *bpf_comment_tmp = ' ';

  while ((bpf_comment_tmp = strchr(bpf_filter, '\n')))
   *bpf_comment_tmp = ' ';


  while (strlen(bpf_filter) > 0 && bpf_filter[strlen(bpf_filter) - 1] == ' ')
   bpf_filter[strlen(bpf_filter) - 1] = '\0';


  if (strlen(bpf_filter) > 0) {
   if (ConfSetFinal("bpf-filter", bpf_filter) != 1) {
    free(bpf_filter);
    do { vb_log_stub("failed to set bpf filter"); } while(0);
    exit(1);
   }
  }
 } else {
  free(bpf_filter);
 }
}