char *func0(char str[]) {
 int len, new_len, space_count = 0, j, i;
 char new_str[1000];
 char *ret_str;

 len = strlen(str);
 for (i = 0; ; i++) {
  if (i >= len)
   break;
  switch(str[i]) {
   case ' ':
    space_count++;
    break;
   default:
    break;
  }
 }

 new_len = len + (2 * space_count);

 if (new_len > 1000) {
  ret_str = "usage: %s <seed> [dump]\n";
  return ret_str;
 }

 j = new_len - 1;
 new_str[new_len] = '\0';

 for (i = len - 1; ; i--) {
  if (i < 0)
   break;
  switch(str[i]) {
   case ' ':
    new_str[j--] = '0';
    new_str[j--] = '2';
    new_str[j--] = '%';
    break;
   default:
    new_str[j--] = str[i];
    break;
  }
 }

 ret_str = (char *)malloc((new_len + 1) * sizeof(char));
 strcpy(ret_str, new_str);

 return ret_str;
}