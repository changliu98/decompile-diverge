void strupr(char *str)
{
 for(;*str != '\0'; str++)
 {
  if(*str >= 97 && *str <= 122)
   *str = (*str)-32;
 }
}