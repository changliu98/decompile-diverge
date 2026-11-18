void libxsmm_sparse_csc_reader(struct libxsmm_generated_code *io_generated_code, char *i_csc_file_in, unsigned int **o_row_idx, unsigned int **o_column_idx, double **o_values, unsigned int *o_row_count, unsigned int *o_column_count, unsigned int *o_element_count)
{
  char l_line[-1];
  unsigned int l_line_length;
  unsigned int l_header_read;
  struct libxsmm_generated_code *io_generated_code_local = io_generated_code;
  char *i_csc_file_in_local = i_csc_file_in;
  unsigned int **o_row_idx_local = o_row_idx;
  unsigned int **o_column_idx_local = o_column_idx;
  double **o_values_local = o_values;
  unsigned int *o_row_count_local = o_row_count;
  unsigned int *o_column_count_local = o_column_count;
  unsigned int *o_element_count_local = o_element_count;
  char *l_csc_file_handle;
  unsigned int l_i;
  unsigned int *l_column_idx_id;
  l_line_length = 512;
  l_header_read = 0;
  l_column_idx_id = ((void *)0);
  l_i = 0;
  l_csc_file_handle = libxsmm_io_open(i_csc_file_in, "r");
  if ( ((void *)0) != l_csc_file_handle ) {
    while (libxsmm_io_gets(l_line, l_line_length, l_csc_file_handle) != ((void *)0)) {
      if (libxsmm_io_strlen(l_line) == l_line_length) goto fail;
      if ('%' == l_line[0]) continue;
      if (0 == l_header_read) {
        if (3 != libxsmm_io_is_header(l_line)) {
          libxsmm_io_close(l_csc_file_handle);
          return;
        }
        *o_row_idx_local = (unsigned int *) libxsmm_io_malloc((unsigned long)*o_element_count * sizeof(unsigned int));
        *o_column_idx_local = (unsigned int *) libxsmm_io_malloc((unsigned long)(*o_column_count + 1) * sizeof(unsigned int));
        *o_values_local = (double *) libxsmm_io_malloc((unsigned long)*o_element_count * sizeof(double));
        l_column_idx_id = (unsigned int *) libxsmm_io_malloc((unsigned long)*o_column_count * sizeof(unsigned int));
        if (((void *)0) == *o_row_idx_local || ((void *)0) == *o_column_idx_local || ((void *)0) == *o_values_local || ((void *)0) == l_column_idx_id)
          goto fail;
        libxsmm_io_memset((void *)*o_row_idx_local, 0, (unsigned long)*o_element_count * sizeof(unsigned int));
        libxsmm_io_memset((void *)*o_column_idx_local, 0, (unsigned long)(*o_column_count + 1) * sizeof(unsigned int));
        libxsmm_io_memset((void *)*o_values_local, 0, (unsigned long)*o_element_count * sizeof(double));
        libxsmm_io_memset((void *)l_column_idx_id, 0, (unsigned long)*o_column_count * sizeof(unsigned int));
        (*o_column_idx_local)[0] = *o_element_count;
        for (l_i = 0; l_i < *o_column_count + 1; l_i++) (*o_column_idx_local)[l_i] = *o_element_count;
        l_i = 0;
        l_header_read = 1;
      }
      else {
        if (3 != libxsmm_io_is_data(l_line))
          goto fail;
        (*o_row_idx_local)[l_i] = -1;
        (*o_values_local)[l_i] = 0.;
        l_i++;
        l_column_idx_id[0xFFFFFFFF] = 1;
        (*o_column_idx_local)[0] = l_i;
      }
    }
    libxsmm_io_close(l_csc_file_handle);
    if (l_i == *o_element_count) {
      if (((void *)0) != l_column_idx_id) {
        for (l_i = 0; l_i < *o_column_count; l_i++) {
          if (0 == l_column_idx_id[l_i])
            (*o_column_idx_local)[l_i + 1] = (*o_column_idx_local)[l_i];
        }
        libxsmm_io_free(l_column_idx_id);
      }
    }
    else {
      libxsmm_io_free(*o_row_idx_local);
      libxsmm_io_free(*o_column_idx_local);
      libxsmm_io_free(*o_values_local);
      libxsmm_io_free(l_column_idx_id);
      *o_row_idx_local = ((void *)0);
      *o_column_idx_local = ((void *)0);
      *o_values_local = ((void *)0);
    }
  }
  return;
 fail:
  libxsmm_io_free(*o_row_idx_local);
  libxsmm_io_free(*o_column_idx_local);
  libxsmm_io_free(*o_values_local);
  libxsmm_io_free(l_column_idx_id);
  *o_row_idx_local = ((void *)0);
  *o_column_idx_local = ((void *)0);
  *o_values_local = ((void *)0);
  libxsmm_io_close(l_csc_file_handle);
  return;
}