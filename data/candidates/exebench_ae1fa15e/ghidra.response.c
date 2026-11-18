uint render_uint32(uint n,char *buff)

{
  uint len;
  char *buff_local;
  uint n_local;
  uint local_c;
  
  if (n == 0) {
    *buff = '0';
    local_c = 1;
  }
  else {
    len = 0;
    for (n_local = n; n_local != 0; n_local = n_local >> 4) {
      buff[len] = "0123456789ABCDEF"[n_local & 0xf];
      len = len + 1;
    }
    local_c = len;
  }
  return local_c;
}