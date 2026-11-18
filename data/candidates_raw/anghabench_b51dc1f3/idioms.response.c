int get_sort_mode(int c)
{
  if (c < 128)
    return tbl_sorting_mode[(int) c];
  else
    return -1;
}