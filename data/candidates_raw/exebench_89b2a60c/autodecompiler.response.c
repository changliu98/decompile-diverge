char *replace_char(char *str, char old, char new)
{
 char *ptr;
 char *ret;

 if (NULL == str || '\0' == *str) {
  ret = str;
  goto end;
 }

 ptr = str;
 while (1) {
  ptr = strchr(ptr, old);
  if (NULL == ptr)
   break;
  *ptr++ = new;
 }

 ret = str;

end:
 return ret;
}