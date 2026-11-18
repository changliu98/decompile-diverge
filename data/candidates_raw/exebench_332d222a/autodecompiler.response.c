void get_row_type_widths(int strings_heap_index_length, int guid_heap_index_length, int blob_heap_index_length, int *widths)
{
 widths[0] = 2 + strings_heap_index_length + (3 * guid_heap_index_length);
 widths[1] = 2 + (2 * strings_heap_index_length);
 widths[2] = 10 + (2 * strings_heap_index_length);
 widths[3] = 0;
 widths[4] = 2 + strings_heap_index_length + blob_heap_index_length;
 widths[5] = 0;
 widths[6] = 10 + strings_heap_index_length + blob_heap_index_length;
 widths[7] = 0;
 widths[8] = 4 + strings_heap_index_length;
 widths[9] = 4;
 widths[10] = 2 + strings_heap_index_length + blob_heap_index_length;
 widths[11] = 4 + blob_heap_index_length;
 widths[12] = 4 + blob_heap_index_length;
}