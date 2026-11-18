void func0(char *str, int encode)
{
 char *s = str;
 int len = strlen(str);
 int num = (len + 2) / 3;
 for (int i = 0; i < num; i++) {
  char temp[4];
  int len2 = (i * 3 + 3 < len) ? 3 : (len - i * 3);
  strncpy(temp, s + i * 3, len2);
  temp[len2] = '\0';
  if (len2 == 3) {
   if (encode) {
    char temp2 = temp[2];
    temp[2] = temp[1];
    temp[1] = temp[0];
    temp[0] = temp2;
   } else {
    char temp2 = temp[0];
    temp[0] = temp[1];
    temp[1] = temp[2];
    temp[2] = temp2;
   }
  }
  strncpy(s + i * 3, temp, len2);
 }
}