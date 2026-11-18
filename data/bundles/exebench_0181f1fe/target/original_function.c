int ellipsis(char *str, int len)
{
 int i = 0, inGBK = 0;
 char *ptr = str;
 if (len < 0 || str == NULL)
  return 0;
 if (len < 3) {
  str[len] = '\0';
  return 1;
 }
 i = len - 3;
 while (*ptr != '\0' && i) {
  if (inGBK) {
   inGBK = 0;
  }
  else if (*ptr & 0x80)
   inGBK = 1;
  ++ptr;
  --i;
 }
 i = 3;
 while(*ptr++ != '\0' && --i)
  ;
 if(*ptr != '\0' && !i){
  str[len] = '\0';
  *--ptr = '.';
  *--ptr = '.';
  if(!inGBK && *--ptr & 0x80)
   *ptr = '.';
 }
 return 1;
}