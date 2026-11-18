char *encode(char *string)
{
 char *str = string;
 int i; int j;
 int space_count = 0;
 int new_length;
 char new_str[1000];
 char *ret;
 for (i = 0; i < (int)strlen(str); i++)
  if (str[i] == ' ')
   space_count++;
 new_length = (int)(strlen(str) + (space_count * 2));
 if (new_length > 1000)
  return "";
 j = new_length - 1;
 new_str[new_length] = '\0';
 for (i = (int)strlen(str) - 1; i >= 0; i--)
  if (str[i] == ' ')
  {
   new_str[j] = '0';
   new_str[j - 1] = '2';
   new_str[j - 2] = '%';
   j = j - 3;
  }
  else
  {
   new_str[j] = str[i];
   j = j - 1;
  }
 ret = (char *)malloc((new_length + 1)*sizeof(char));
 strcpy(ret, new_str);
 return ret;
}