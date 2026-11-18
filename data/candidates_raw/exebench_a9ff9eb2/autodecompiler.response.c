char *itoa(unsigned int val, char *buf)
{
 int i = 0;
 char hex[] = "0123456789ABCDEF";
 for(i = 0; i < 9; i++) {
  buf[9-i] = hex[val & 0xF];
  val >>= 4;
 }
 buf[0] = '0';
 buf[1] = 'x';
 buf[10] = '\n';
 buf[11] = '\0';

 return buf;
}