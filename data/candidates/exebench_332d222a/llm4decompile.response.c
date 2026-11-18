void fill_row_type_widths(
  int strings_heap_index_length,
  int guid_heap_index_length,
  int blob_heap_index_length,
  int row_type_widths[]
) {
  int i = 0;


  row_type_widths[i++] = 2 + guid_heap_index_length * 3 + strings_heap_index_length;

  row_type_widths[i++] = 2 + strings_heap_index_length * 2;

  row_type_widths[i++] = 10 + strings_heap_index_length * 2;

  row_type_widths[i++] = 0;

  row_type_widths[i++] = 2 + blob_heap_index_length + strings_heap_index_length;

  row_type_widths[i++] = 0;

  row_type_widths[i++] = 10 + blob_heap_index_length + strings_heap_index_length;

  row_type_widths[i++] = 0;

  row_type_widths[i++] = 4 + strings_heap_index_length;

  row_type_widths[i++] = 4;

  row_type_widths[i++] = 2 + blob_heap_index_length + strings_heap_index_length;

  row_type_widths[i++] = 4 + blob_heap_index_length;

  row_type_widths[i++] = 4 + blob_heap_index_length;
}