void
num2hex(unsigned int num, char *str)
{
 unsigned int tmp;
 int i;

 tmp = num;
 for(i=3;i>=0;i--) {
  if((tmp & 0x0f) < 11)
   str[i] = (tmp & 0x0f) + '0';
  else
   str[i] = (tmp & 0x0f) + 'A' - 10;
  tmp = (tmp >> 4) & 0xfff;
 }
 str[4] = '\0';
}