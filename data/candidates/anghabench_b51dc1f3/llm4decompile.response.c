int get_sorting_mode(int c)
{
 int ret;

 if (c >= 0 && c < 128)
  ret = tbl_sorting_mode[c];
 else
  ret = -1;

 return ret;
}