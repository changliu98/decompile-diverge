void dopr_outch(char *buffer,size_t *currlen,size_t maxlen,char c)

{
  char c_local;
  size_t maxlen_local;
  size_t *currlen_local;
  char *buffer_local;
  
  if (*currlen < maxlen) {
    buffer[*currlen] = c;
  }
  *currlen = *currlen + 1;
  return;
}