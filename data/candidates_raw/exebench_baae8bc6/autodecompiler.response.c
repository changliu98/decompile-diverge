void reverse(char *s) {
 char *end = s;
 while (*end++ != '\0') {}
 end -= 2;

 while (s < end) {
  *s -= *end;
  *end += *s;
  *s = *end - *s;
  s++;
  end--;
 }
}