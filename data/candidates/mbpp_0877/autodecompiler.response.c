void func0(char *s)
{
 int c, i, j, len;

 len = strlen(s);

 for (i = 0; i < len-1; i++)
  for (j = i+1; j < len; j++)
   if (s[i] > s[j]) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
   }
}