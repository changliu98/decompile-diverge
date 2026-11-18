void swap_float_4(void *ptr)
{
  int *int_ptr = (int*)ptr;
  *int_ptr = (((*int_ptr & 0xff) << 24) |
             (((*int_ptr & 0xff00) << 8) & 0xff0000) |
             (((*int_ptr & 0xff0000) >> 8) & 0xff00) |
             (((*int_ptr & 0xff000000) >> 24)));
}