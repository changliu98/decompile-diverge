void swap_float_4(unsigned char *header) {
 int *intHeader = (int*)header;

 *intHeader = (((*intHeader >> 24) & 0x000000FF) << 0) |
  (((*intHeader >> 16) & 0x000000FF) << 8) |
  (((*intHeader >> 8) & 0x000000FF) << 16) |
  (((*intHeader >> 0) & 0x000000FF) << 24);
}