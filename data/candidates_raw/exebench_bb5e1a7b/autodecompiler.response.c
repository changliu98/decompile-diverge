char *get_double(char *s,double *d)
{
 int i,j,k;
 double sign=1.0;
 char *t;

 while(1)
 {
  if(*s=='+' || *s=='-') break;
  s++;
 }
 if(*s=='-')
  sign = -sign;
 s++;

 j = 0;
 k = 0;
 double base = 1.0;
 while(1)
 {
  if(*s>'9' || *s<'0') break;
  j = j*10 + *s++ - '0';
 }
 if(*s=='\0')
 {
  *d = sign*j;
  t = s;
 }
 else
 {
  if(*s=='.')
  {
   s++;
   while(1)
   {
    if(*s>'9' || *s<'0') break;
    k = k*10 + *s++ - '0';
    base *= 10.0;
   }
  }
  *d = sign*(j+k/base);
  t = s;
 }
 return t;
}