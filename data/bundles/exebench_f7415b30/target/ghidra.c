int dummywc_mbtowc(int *pwc,char *s,size_t n)

{
  size_t n_local;
  char *s_local;
  int *pwc_local;
  undefined4 local_c;
  
  if ((n == 0) || (*s == '\0')) {
    local_c = 0;
  }
  else {
    *pwc = (int)*s;
    local_c = 1;
  }
  return local_c;
}