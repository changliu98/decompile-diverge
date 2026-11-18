void func0(char *s, int encode)
{
 int len = strlen(s);
 int i;
 char tmp[4];
 char c1, c2, c3;

 for (i = 0; i < (len + 2) / 3; i++) {
  int num = len - i * 3;
  if (num > 3) {
   num = 3;
  }
  strncpy(tmp, s + i * 3, num);
  tmp[num] = '\0';
  c1 = tmp[0];
  c2 = tmp[1];
  c3 = tmp[2];
  if (num == 3) {
   if (encode) {
    tmp[0] = c3;
    tmp[1] = c2;
    tmp[2] = c1;
   } else {
    tmp[0] = c2;
    tmp[1] = c3;
    tmp[2] = c1;
   }
  }
  strncpy(s + i * 3, tmp, num);
 }
}