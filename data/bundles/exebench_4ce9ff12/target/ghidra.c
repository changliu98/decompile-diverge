size_t defaultPrevCharLen(char *buf,size_t buf_len,size_t pos,size_t *col_len)

{
  size_t *col_len_local;
  size_t pos_local;
  size_t buf_len_local;
  char *buf_local;
  
  if (col_len != (size_t *)0x0) {
    *col_len = 1;
  }
  return 1;
}