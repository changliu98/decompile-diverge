int func0(char *s1, char *s2)
{
 int len1 = strlen(s1);
 int len2 = strlen(s2);

 if (len1 % len2 != 0) {
  int flag = 0;
 } else {
  int i;
  int flag = 1;
  for (i = 0; i < len1; i++) {
   if (s1[i] != s2[i%len2]) {
    flag = 0;
    break;
   }
  }
 }

 return flag;
}