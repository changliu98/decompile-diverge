int OS_file_open(unsigned long *p_file_handle, const char *p_filename)
{
 *p_file_handle = open(p_filename, O_RDONLY);
 if (-1 == *p_file_handle)
  return 0x1004;

 return 0;
}