void __cdecl libxsmm_sparse_csc_reader(
        libxsmm_generated_code *io_generated_code,
        const char *i_csc_file_in,
        unsigned int **o_row_idx,
        unsigned int **o_column_idx,
        double **o_values,
        unsigned int *o_row_count,
        unsigned int *o_column_count,
        unsigned int *o_element_count)
{
  unsigned int l_i; // [rsp+1Ch] [rbp-254h]
  unsigned int l_ia; // [rsp+1Ch] [rbp-254h]
  unsigned int l_ib; // [rsp+1Ch] [rbp-254h]
  unsigned int *l_column_idx_id; // [rsp+20h] [rbp-250h]
  unsigned int l_header_read; // [rsp+2Ch] [rbp-244h]
  char l_line[513]; // [rsp+30h] [rbp-240h] BYREF
  unsigned int l_line_length; // [rsp+234h] [rbp-3Ch]
  FILE *l_csc_file_handle; // [rsp+238h] [rbp-38h]
  unsigned int *o_row_counta; // [rsp+240h] [rbp-30h]
  double **o_valuesa; // [rsp+248h] [rbp-28h]
  unsigned int **o_column_idxa; // [rsp+250h] [rbp-20h]
  unsigned int **o_row_idxa; // [rsp+258h] [rbp-18h]
  const char *i_csc_file_ina; // [rsp+260h] [rbp-10h]
  libxsmm_generated_code *io_generated_codea; // [rsp+268h] [rbp-8h]

  io_generated_codea = io_generated_code;
  i_csc_file_ina = i_csc_file_in;
  o_row_idxa = o_row_idx;
  o_column_idxa = o_column_idx;
  o_valuesa = o_values;
  o_row_counta = o_row_count;
  l_line_length = 512;
  l_header_read = 0;
  l_column_idx_id = 0LL;
  l_i = 0;
  l_csc_file_handle = fopen(i_csc_file_in, "r");
  if ( l_csc_file_handle )
  {
    while ( fgets(l_line, 512, l_csc_file_handle) )
    {
      if ( strlen(l_line) == 512 )
        goto LABEL_18;
      if ( l_line[0] != 37 )
      {
        if ( l_header_read )
        {
          if ( (unsigned int)__isoc99_sscanf() != 3 )
            goto LABEL_18;
          (*o_row_idxa)[l_i] = -1;
          (*o_valuesa)[l_i++] = 0.0;
          l_column_idx_id[0xFFFFFFFFLL] = 1;
          **o_column_idxa = l_i;
        }
        else
        {
          if ( (unsigned int)__isoc99_sscanf() != 3 )
          {
            fclose(l_csc_file_handle);
            return;
          }
          *o_row_idxa = (unsigned int *)malloc(4LL * *o_element_count);
          *o_column_idxa = (unsigned int *)malloc(4 * (*o_column_count + 1LL));
          *o_valuesa = (double *)malloc(8LL * *o_element_count);
          l_column_idx_id = (unsigned int *)malloc(4LL * *o_column_count);
          if ( !*o_row_idxa || !*o_column_idxa || !*o_valuesa || !l_column_idx_id )
          {
LABEL_18:
            free(*o_row_idxa);
            free(*o_column_idxa);
            free(*o_valuesa);
            free(l_column_idx_id);
            *o_row_idxa = 0LL;
            *o_column_idxa = 0LL;
            *o_valuesa = 0LL;
            fclose(l_csc_file_handle);
            return;
          }
          memset(*o_row_idxa, 0, 4LL * *o_element_count);
          memset(*o_column_idxa, 0, 4 * (*o_column_count + 1LL));
          memset(*o_valuesa, 0, 8LL * *o_element_count);
          memset(l_column_idx_id, 0, 4LL * *o_column_count);
          for ( l_ia = 0; l_ia <= *o_column_count; ++l_ia )
            (*o_column_idxa)[l_ia] = *o_element_count;
          **o_column_idxa = 0;
          l_i = 0;
          l_header_read = 1;
        }
      }
    }
    fclose(l_csc_file_handle);
    if ( l_i == *o_element_count )
    {
      if ( l_column_idx_id )
      {
        for ( l_ib = 0; l_ib < *o_column_count; ++l_ib )
        {
          if ( !l_column_idx_id[l_ib] )
            (*o_column_idxa)[l_ib + 1] = (*o_column_idxa)[l_ib];
        }
        free(l_column_idx_id);
      }
    }
    else
    {
      free(*o_row_idxa);
      free(*o_column_idxa);
      free(*o_valuesa);
      free(l_column_idx_id);
      *o_row_idxa = 0LL;
      *o_column_idxa = 0LL;
      *o_valuesa = 0LL;
    }
  }
}