int
get_count(char *str)
{
 int i, j;
 int len;
 int count;

 count = 0;
 len = strlen(str);
 i = 0;
 while (i < len) {
  j = 1;
  while (j <= len - i) {
   if (check_Equality(str, i, i + j - 1))
    count++;
   j++;
  }
  i++;
 }
 return (count);
}