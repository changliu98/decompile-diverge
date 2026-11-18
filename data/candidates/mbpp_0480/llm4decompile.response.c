char func0(char *str1)
{
 int ctr[256];
 memset(ctr, 0, sizeof(ctr));
 int max = -1;
 char ch = 0;
 int length = strlen(str1);
 for (int i = 0; i < length; i++) {
  ctr[str1[i]]++;
 }
 for (int i = 0; i < length; i++) {
  if (ctr[str1[i]] > max) {
   max = ctr[str1[i]];
   ch = str1[i];
  }
 }
 return ch;
}