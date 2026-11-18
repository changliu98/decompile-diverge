char * func0(char *str)

{
  size_t sVar1;
  int st;
  int maxlen;
  int currlen;
  int i;
  int n;
  char *str_local;
  char *local_10;
  
  sVar1 = strlen(str);
  currlen = 0;
  maxlen = 0;
  st = -1;
  for (i = 0; i < (int)sVar1; i = i + 1) {
    if (str[i] == ' ') {
      if ((currlen % 2 == 0) && (maxlen < currlen)) {
        maxlen = currlen;
        st = i - currlen;
      }
      currlen = 0;
    }
    else {
      currlen = currlen + 1;
    }
  }
  if ((currlen % 2 == 0) && (maxlen < currlen)) {
    maxlen = currlen;
    st = i - currlen;
  }
  if (st == -1) {
    local_10 = "-1";
  }
  else {
    strncpy(func0::result,str + st,(long)maxlen);
    func0::result[maxlen] = '\0';
    local_10 = func0::result;
  }
  return local_10;
}