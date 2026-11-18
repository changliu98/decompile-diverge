void libxsmm_sparse_csc_reader
               (libxsmm_generated_code *io_generated_code,char *i_csc_file_in,uint **o_row_idx,
               uint **o_column_idx,double **o_values,uint *o_row_count,uint *o_column_count,
               uint *o_element_count)

{
  int iVar1;
  FILE *__stream;
  char *pcVar2;
  size_t sVar3;
  uint *puVar4;
  double *pdVar5;
  double l_value;
  uint l_column;
  uint l_row;
  uint l_i;
  uint *l_column_idx_id;
  uint l_header_read;
  char l_line [513];
  uint l_line_length;
  FILE *l_csc_file_handle;
  uint *o_row_count_local;
  double **o_values_local;
  uint **o_column_idx_local;
  uint **o_row_idx_local;
  char *i_csc_file_in_local;
  libxsmm_generated_code *io_generated_code_local;
  
  l_header_read = 0;
  l_column_idx_id = (uint *)0x0;
  l_i = 0;
  __stream = fopen(i_csc_file_in,"r");
  if (__stream != (FILE *)0x0) {
    while (pcVar2 = fgets(l_line,0x200,__stream), pcVar2 != (char *)0x0) {
      sVar3 = strlen(l_line);
      if (sVar3 == 0x200) {
        free(*o_row_idx);
        free(*o_column_idx);
        free(*o_values);
        free(l_column_idx_id);
        *o_row_idx = (uint *)0x0;
        *o_column_idx = (uint *)0x0;
        *o_values = (double *)0x0;
        fclose(__stream);
        return;
      }
      if (l_line[0] != '%') {
        if (l_header_read == 0) {
          iVar1 = __isoc99_sscanf(l_line,"%u %u %u",o_row_count,o_column_count,o_element_count);
          if (iVar1 != 3) {
            fclose(__stream);
            return;
          }
          puVar4 = malloc((ulong)*o_element_count << 2);
          *o_row_idx = puVar4;
          puVar4 = malloc(((ulong)*o_column_count + 1) * 4);
          *o_column_idx = puVar4;
          pdVar5 = malloc((ulong)*o_element_count << 3);
          *o_values = pdVar5;
          l_column_idx_id = malloc((ulong)*o_column_count << 2);
          if ((((*o_row_idx == (uint *)0x0) || (*o_column_idx == (uint *)0x0)) ||
              (*o_values == (double *)0x0)) || (l_column_idx_id == (uint *)0x0)) {
            free(*o_row_idx);
            free(*o_column_idx);
            free(*o_values);
            free(l_column_idx_id);
            *o_row_idx = (uint *)0x0;
            *o_column_idx = (uint *)0x0;
            *o_values = (double *)0x0;
            fclose(__stream);
            return;
          }
          memset(*o_row_idx,0,(ulong)*o_element_count << 2);
          memset(*o_column_idx,0,((ulong)*o_column_count + 1) * 4);
          memset(*o_values,0,(ulong)*o_element_count << 3);
          memset(l_column_idx_id,0,(ulong)*o_column_count << 2);
          for (l_i = 0; l_i <= *o_column_count; l_i = l_i + 1) {
            (*o_column_idx)[l_i] = *o_element_count;
          }
          **o_column_idx = 0;
          l_i = 0;
          l_header_read = 1;
        }
        else {
          l_row = 0;
          l_column = 0;
          l_value = 0.0;
          iVar1 = __isoc99_sscanf(l_line,"%u %u %lf",&l_row,&l_column,&l_value);
          if (iVar1 != 3) {
            free(*o_row_idx);
            free(*o_column_idx);
            free(*o_values);
            free(l_column_idx_id);
            *o_row_idx = (uint *)0x0;
            *o_column_idx = (uint *)0x0;
            *o_values = (double *)0x0;
            fclose(__stream);
            return;
          }
          l_row = l_row - 1;
          (*o_row_idx)[l_i] = l_row;
          (*o_values)[l_i] = l_value;
          l_i = l_i + 1;
          l_column_idx_id[l_column - 1] = 1;
          (*o_column_idx)[l_column] = l_i;
          l_column = l_column - 1;
        }
      }
    }
    fclose(__stream);
    if (l_i == *o_element_count) {
      if (l_column_idx_id != (uint *)0x0) {
        for (l_i = 0; l_i < *o_column_count; l_i = l_i + 1) {
          if (l_column_idx_id[l_i] == 0) {
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
      *o_row_idx = (uint *)0x0;
      *o_column_idx = (uint *)0x0;
      *o_values = (double *)0x0;
    }
  }
  return;
}