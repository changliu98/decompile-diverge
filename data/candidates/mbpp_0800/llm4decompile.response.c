void func0(char *text, char *result)
{
 int i, j;

 for (i = 0, j = 0; text[i] != '\0'; i++) {
  if (!((*__ctype_b_loc ())[(int) ((unsigned char) text[i])] & 0x2000)) {
   result[j++] = text[i];
  }
 }
 result[j] = '\0';
}