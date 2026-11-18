int C_Utils_compare_float_ptr(void *a, void *b)
{
  if (*(float *)a == *(float *)b)
    return 0;
  return (*(float *)a < *(float *)b ? -1 : 1);
}