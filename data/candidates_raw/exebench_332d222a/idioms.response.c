void get_row_type_widths(int strings_heap_index_length, int guid_heap_index_length, int blob_heap_index_length, int *row_type_widths)
{
  row_type_widths[0] = strings_heap_index_length + guid_heap_index_length * 3 + 2;
  row_type_widths[1] = strings_heap_index_length * 2 + 2;
  row_type_widths[2] = strings_heap_index_length * 2 + 10;
  row_type_widths[3] = 0;
  row_type_widths[4] = strings_heap_index_length + blob_heap_index_length + 2;
  row_type_widths[5] = 0;
  row_type_widths[6] = strings_heap_index_length * 2 + blob_heap_index_length * 2 + 10;
  row_type_widths[7] = 0;
  row_type_widths[8] = strings_heap_index_length + 4;
  row_type_widths[9] = 4;
  row_type_widths[10] = strings_heap_index_length + blob_heap_index_length + 2;
  row_type_widths[11] = blob_heap_index_length + 4;
  row_type_widths[12] = blob_heap_index_length + 4;
}