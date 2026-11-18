int func0(char *s, int n)
{
 int i, j, k, t, num1, num2;
 char str1[10];
 char str2[10];

 memset(str1, 0, 10);
 memset(str2, 0, 10);

 i = 0;
 j = 0;
 k = 0;
 while (s[i] != '\0') {
  if (s[i] & 0x800) {
   if (k == 0)
    str1[j++] = s[i];
   else
    str2[j++] = s[i];
  } else {
   if (k == 0 && j > 0) {
    k = 1;
    j = 0;
   }
  }
  i++;
 }

 num1 = atoi(str1);
 num2 = atoi(str2);

 return n - num1 - num2;
}