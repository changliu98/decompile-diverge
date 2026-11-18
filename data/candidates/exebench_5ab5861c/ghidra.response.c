char * itoa(long n,char *str,long radix)

{
  char cVar1;
  char temp;
  char *head;
  char *p;
  char digit [37];
  long radix_local;
  char *str_local;
  long n_local;
  char *local_10;
  
  memcpy(digit,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",0x25);
  local_10 = str;
  if ((((str != (char *)0x0) && (1 < radix)) && (radix < 0x25)) && ((radix == 10 || (-1 < n)))) {
    if (n == 0) {
      local_10 = str + 1;
      *str = '0';
      *local_10 = '\0';
    }
    else {
      p = str;
      n_local = n;
      if ((radix == 10) && (n < 0)) {
        p = str + 1;
        *str = '-';
        n_local = -n;
      }
      for (; n_local != 0; n_local = n_local / radix) {
        *p = digit[n_local % radix];
        p = p + 1;
      }
      *p = '\0';
      for (head = str; p = p + -1, head < p; head = head + 1) {
        cVar1 = *head;
        *head = *p;
        *p = cVar1;
      }
    }
  }
  return local_10;
}