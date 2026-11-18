int __cdecl OS_file_open(unsigned __int64 *p_file_handle, const char *p_filename)
{
  *p_file_handle = open(p_filename, 0);
  if ( *p_file_handle == -1LL )
    return 4100;
  else
    return 0;
}