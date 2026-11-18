void itoa(int dst,char *src)

{
  char cVar1;
  int udst;
  int mod;
  char exc;
  char *str2;
  char *str1;
  char *src_local;
  int dst_local;
  
  udst = dst;
  str1 = src;
  if (dst < 0) {
    udst = -dst;
    *src = '-';
    str1 = src + 1;
  }
  str2 = str1;
  do {
    *str2 = (char)(udst % 10) + '0';
    udst = udst / 10;
    str2 = str2 + 1;
  } while (udst != 0);
  *str2 = '\0';
  for (; str2 = str2 + -1, str1 < str2; str1 = str1 + 1) {
    cVar1 = *str1;
    *str1 = *str2;
    *str2 = cVar1;
  }
  return;
}