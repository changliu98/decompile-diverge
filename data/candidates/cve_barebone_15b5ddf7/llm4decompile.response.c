void libxsmm_sparse_csc_reader(libxsmm_generated_code *io_generated_code, const char *i_csc_file_in, unsigned int **o_row_idx, unsigned int **o_column_idx, double **o_values, unsigned int *o_row_count, unsigned int *o_column_count, unsigned int *o_element_count)
{
  unsigned int l_header_read = 0;
  unsigned int l_i = 0;
  unsigned int *l_column_idx_id = 0;
  FILE *l_csc_file_handle = fopen(i_csc_file_in, "r");
  if (l_csc_file_handle) {
    char l_line[512];
    while (fgets(l_line, 512, l_csc_file_handle)) {
      unsigned int l_line_length = strlen(l_line);
      if (l_line_length == 512) {
        free(*o_row_idx);
        free(*o_column_idx);
        free(*o_values);
        free(l_column_idx_id);
        *o_row_idx = 0;
        *o_column_idx = 0;
        *o_values = 0;
        fclose(l_csc_file_handle);
        return;
      }
      if (l_line[0] != '%') {
        if (!l_header_read) {
          if (__isoc99_sscanf(l_line, "%u %u %u", o_row_count, o_column_count, o_element_count) == 3) {
            *o_row_idx = (unsigned int*)malloc(*o_element_count * sizeof(unsigned int));
            *o_column_idx = (unsigned int*)malloc((*o_column_count + 1) * sizeof(unsigned int));
            *o_values = (double*)malloc(*o_element_count * sizeof(double));
            l_column_idx_id = (unsigned int*)malloc(*o_column_count * sizeof(unsigned int));
            if (*o_row_idx && *o_column_idx && *o_values && l_column_idx_id) {
              memset(*o_row_idx, 0, *o_element_count * sizeof(unsigned int));
              memset(*o_column_idx, 0, (*o_column_count + 1) * sizeof(unsigned int));
              memset(*o_values, 0, *o_element_count * sizeof(double));
              memset(l_column_idx_id, 0, *o_column_count * sizeof(unsigned int));
              for (l_i = 0; l_i <= *o_column_count; l_i++) {
                (*o_column_idx)[l_i] = *o_element_count;
              }
              (*o_column_idx)[0] = 0;
              l_i = 0;
              l_header_read = 1;
            }
            else {
              free(*o_row_idx);
              free(*o_column_idx);
              free(*o_values);
              free(l_column_idx_id);
              *o_row_idx = 0;
              *o_column_idx = 0;
              *o_values = 0;
              fclose(l_csc_file_handle);
              return;
            }
          }
          else {
            fclose(l_csc_file_handle);
            return;
          }
        }
        else {
          unsigned int l_row = 0;
          unsigned int l_column = 0;
          double l_value = 0;
          if (__isoc99_sscanf(l_line, "%u %u %lf", &l_row, &l_column, &l_value) == 3) {
            l_row--;
            (*o_row_idx)[l_i] = l_row;
            (*o_values)[l_i] = l_value;
            l_i++;
            l_column_idx_id[l_column - 1] = 1;
            (*o_column_idx)[l_column] = l_i;
            l_column--;
          }
          else {
            free(*o_row_idx);
            free(*o_column_idx);
            free(*o_values);
            free(l_column_idx_id);
            *o_row_idx = 0;
            *o_column_idx = 0;
            *o_values = 0;
            fclose(l_csc_file_handle);
            return;
          }
        }
      }
    }
    fclose(l_csc_file_handle);
    if (l_i == *o_element_count) {
      if (l_column_idx_id) {
        for (l_i = 0; l_i < *o_column_count; l_i++) {
          if (!l_column_idx_id[l_i]) {
            (*o_column_idx)[l_i + 1] = (*o_column_idx)[l_i];
          }
        }
        free(l_column_idx_id);
      }
    }
    else {
      free(*o_row_idx);
      free(*o_column_idx);
      free(*o_values);
      free(l_column_idx_id);
      *o_row_idx = 0;
      *o_column_idx = 0;
      *o_values = 0;
    }
  }
}