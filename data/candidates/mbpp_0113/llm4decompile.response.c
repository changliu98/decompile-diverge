int func0(char *text)
{
 int i, len;

 len = strlen(text);

 while (*text == ' ') {
  text++;
  len--;
 }

 if (len < 1)
  return -1;

 if (*text == '+' || *text == '-') {
  for (i = 1; i < len; i++) {
   if (text[i] < '0' || text[i] > '9')
    return 0;
  }
 } else {
  for (i = 0; i < len; i++) {
   if (text[i] < '0' || text[i] > '9')
    return 0;
  }
 }

 return 1;
}