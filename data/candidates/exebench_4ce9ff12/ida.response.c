size_t __cdecl defaultPrevCharLen(const char *buf, size_t buf_len, size_t pos, size_t *col_len)
{
  if ( col_len )
    *col_len = 1LL;
  return 1LL;
}