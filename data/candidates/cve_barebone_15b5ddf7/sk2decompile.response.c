void libxsmm_sparse_csc_reader(libxsmm_mmfunction_handle *mmf_handle,
                               const char *filename, unsigned int **row_ind,
                               unsigned int **col_ptr, double **val,
                               unsigned int *m, unsigned int *n,
                               unsigned int *nnz) {
  FILE *fp;
  char line[512];
  unsigned int line_size = 512;
  unsigned int line_count = 0;
  unsigned int *col_ptr_tmp = NULL;
  unsigned int nnz_count = 0;
  fp = fopen(filename, "r");
  if (fp == NULL) return;
  while (fgets(line, line_size, fp) != NULL) {
    if (strlen(line) == line_size) {
      free(*row_ind);
      free(*col_ptr);
      free(*val);
      free(col_ptr_tmp);
      *row_ind = NULL;
      *col_ptr = NULL;
      *val = NULL;
      fclose(fp);
      return;
    }
    if (line[0] == '%') continue;
    if (line_count == 0) {
      if (sscanf(line, "%u %u %u", m, n, nnz) != 3) {
        fclose(fp);
        return;
      }
      *row_ind = (unsigned int *)malloc(sizeof(unsigned int) * (*nnz));
      *col_ptr = (unsigned int *)malloc(sizeof(unsigned int) * (*n + 1));
      *val = (double *)malloc(sizeof(double) * (*nnz));
      col_ptr_tmp = (unsigned int *)malloc(sizeof(unsigned int) * (*n));
      if (*row_ind == NULL || *col_ptr == NULL || *val == NULL ||
          col_ptr_tmp == NULL) {
        free(*row_ind);
        free(*col_ptr);
        free(*val);
        free(col_ptr_tmp);
        *row_ind = NULL;
        *col_ptr = NULL;
        *val = NULL;
        fclose(fp);
        return;
      }
      memset(*row_ind, 0, sizeof(unsigned int) * (*nnz));
      memset(*col_ptr, 0, sizeof(unsigned int) * (*n + 1));
      memset(*val, 0, sizeof(double) * (*nnz));
      memset(col_ptr_tmp, 0, sizeof(unsigned int) * (*n));
      unsigned int i;
      for (i = 0; i <= *n; i++) {
        (*col_ptr)[i] = *nnz;
      }
      (*col_ptr)[0] = 0;
      nnz_count = 0;
      line_count = 1;
    } else {
      if (sscanf(line, "%u %u %lf", &((*row_ind)[nnz_count]),
                 &((*col_ptr)[nnz_count]), &((*val)[nnz_count])) != 3) {
        free(*row_ind);
        free(*col_ptr);
        free(*val);
        free(col_ptr_tmp);
        *row_ind = NULL;
        *col_ptr = NULL;
        *val = NULL;
        fclose(fp);
        return;
      }
      (*row_ind)[nnz_count]--;
      (*val)[nnz_count] = 0.0;
      col_ptr_tmp[(*col_ptr)[nnz_count] - 1] = 1;
      nnz_count++;
    }
  }
  fclose(fp);
  if (nnz_count != *nnz) {
    free(*row_ind);
    free(*col_ptr);
    free(*val);
    free(col_ptr_tmp);
    *row_ind = NULL;
    *col_ptr = NULL;
    *val = NULL;
    return;
  }
  if (col_ptr_tmp != NULL) {
    unsigned int i;
    for (i = 0; i < *n; i++) {
      if (col_ptr_tmp[i] == 0) {
        (*col_ptr)[i + 1] = (*col_ptr)[i];
      }
    }
    free(col_ptr_tmp);
  }
}