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
  unsigned int l_i, l_ia, l_ib;
  unsigned int *l_column_idx_id = NULL;
  unsigned int l_header_read = 0;
  char l_line[513];
  FILE *l_csc_file_handle;

  l_csc_file_handle = fopen(i_csc_file_in, "r");
  if ( l_csc_file_handle )
  {
    while ( fgets(l_line, 512, l_csc_file_handle) )
    {
      if ( strlen(l_line) == 512 )
        goto LABEL_18;
        
      if ( l_line[0] != '%' )
      {
        if ( l_header_read )
        {
          unsigned int row, col;
          double val;
          
          if ( __isoc99_sscanf(l_line, "%u %u %lf", &row, &col, &val) != 3 )
            goto LABEL_18;
            
          (*o_row_idx)[l_i] = row - 1;
          (*o_values)[l_i] = val;
          l_column_idx_id[col - 1] = 1;
          l_i++;
          **o_column_idx = l_i;
        }
        else
        {
          if ( __isoc99_sscanf(l_line, "%u %u %u", o_row_count, o_column_count, o_element_count) != 3 )
          {
            fclose(l_csc_file_handle);
            return;
          }
          
          *o_row_idx = (unsigned int *)malloc(4LL * *o_element_count);
          *o_column_idx = (unsigned int *)malloc(4 * (*o_column_count + 1LL));
          *o_values = (double *)malloc(8LL * *o_element_count);
          l_column_idx_id = (unsigned int *)malloc(4LL * *o_column_count);
          
          if ( !*o_row_idx || !*o_column_idx || !*o_values || !l_column_idx_id )
          {
LABEL_18:
            free(*o_row_idx);
            free(*o_column_idx);
            free(*o_values);
            free(l_column_idx_id);
            *o_row_idx = NULL;
            *o_column_idx = NULL;
            *o_values = NULL;
            fclose(l_csc_file_handle);
            return;
          }
          
          memset(*o_row_idx, 0, 4LL * *o_element_count);
          memset(*o_column_idx, 0, 4 * (*o_column_count + 1LL));
          memset(*o_values, 0, 8LL * *o_element_count);
          memset(l_column_idx_id, 0, 4LL * *o_column_count);
          
          for ( l_ia = 0; l_ia <= *o_column_count; ++l_ia )
            (*o_column_idx)[l_ia] = *o_element_count;
            
          **o_column_idx = 0;
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
            (*o_column_idx)[l_ib + 1] = (*o_column_idx)[l_ib];
        }
        free(l_column_idx_id);
      }
    }
    else
    {
      free(*o_row_idx);
      free(*o_column_idx);
      free(*o_values);
      free(l_column_idx_id);
      *o_row_idx = NULL;
      *o_column_idx = NULL;
      *o_values = NULL;
    }
  }
}