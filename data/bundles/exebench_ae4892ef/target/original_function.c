char * my_strcpy(char *dst,char *str)
{
 char *destination = dst;
 while( '\0' != *str)
 {
  *dst = *str;
  str++;
  dst++;
 }
 *dst = '\0';
 return destination;
}