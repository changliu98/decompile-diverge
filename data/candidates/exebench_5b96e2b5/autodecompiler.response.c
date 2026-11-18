void reverse(char *s) {
 char *end = s;
 while (*end != '\0') {
  end++;
 }
 end--;

 while (s < end) {
  char tmp = *s;
  *s = *end;
  *end = tmp;

  s++;
  end--;
 }
}