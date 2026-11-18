char* func0(const char* str)
{
 int i, space_count = 0;
 int len = strlen(str);
 char new_str[1000];
 char *ret_str;

 for (i = 0; i < len; i++)
  if (str[i] == ' ')
   space_count++;

 if (len + 2 * space_count > 1000)
  return "";

 new_str[len + 2 * space_count] = '\0';

 for (i = len - 1; i >= 0; i--)
  if (str[i] == ' ') {
   new_str[--len] = '0';
   new_str[--len] = '2';
   new_str[--len] = '%';
  }
  else
   new_str[--len] = str[i];

 ret_str = (char*)malloc(sizeof(char) * (len + 2 * space_count + 1));
 strcpy(ret_str, new_str);

 return ret_str;
}