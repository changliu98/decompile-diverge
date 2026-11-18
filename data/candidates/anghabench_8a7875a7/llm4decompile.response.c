char hex_char(unsigned char x)
{
 if (x > 9) {
  if (x > 15)
   return '?';
  return 'a' + x - 10;
 }
 return '0' + x;
}