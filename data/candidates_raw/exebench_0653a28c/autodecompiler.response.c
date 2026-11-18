void reverse(char *s) {
 char *end = s;
 char tmp;
 char *begin = s;

 while (*end++ != '\0') {
 }

 end--;

 while (begin < end) {
  tmp = *begin;
  *begin = *end;
  *end = tmp;
  begin++;
  end--;
 }
}