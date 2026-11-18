int f_open(void **p_file_handle, char *p_filename)
{
  int ret = 0;
  *p_file_handle = (void *) open(p_filename, 00);
  if (*p_file_handle == (void *) -1)
  {
    ret = 4100;
  }
  return ret;
}