static void set_nb(char const *s, char c, int *nb)
{
 int i1;
 int i2;

 i1 = 0;
 i2 = 0;
 while (s[i1] != '\0') {
  if (i1 == i2 && s[i1] == c) {
   i1++;
   i2++;
  } else {
   if (s[i2] == c || s[i2] == '\0') {
    (*nb)++;
    i1 = i2;
   } else
    i2++;
  }
 }
}