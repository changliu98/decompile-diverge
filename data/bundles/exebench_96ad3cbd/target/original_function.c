static char* maybeint(char* q, int* dst)
{
 if(*q >= '0' && *q <= '9') {
  int num = 0;

  while(*q >= '0' && *q <= '9')
   num = num*10 + (*q++ - '0');

  *dst = num;
 } else {
  *dst = 0;
 }

 return q;
}