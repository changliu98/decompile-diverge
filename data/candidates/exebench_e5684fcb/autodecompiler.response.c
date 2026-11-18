int reverse(char *s) {
 char *end = s;
 char *begin = s;

 while(*end++ != '\0');

 end--;
 end--;

 while(1) {
  if(begin >= end)
   break;

  *begin ^= *end;
  *end ^= *begin;
  *begin ^= *end;

  begin++;
  end--;
 }

 return 0;
}