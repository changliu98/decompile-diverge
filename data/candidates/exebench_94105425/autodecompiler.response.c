void strrev(char *s) {
 char *end = s;
 char tmp;

 while (1) {
  if (end == NULL || *end == '\0') {
   break;
  }
  end++;
 }

 end--;

 while (1) {
  if (s >= end) {
   break;
  }
  tmp = *s ^ *end;
  *s ^= tmp;
  *end ^= tmp;
  *s ^= tmp;
  s++;
  end--;
 }
}