static int
get_nbits(unsigned char b)
{
 int n;

 switch (b & 0x7) {
 case 0:
  n = 1;
  break;
 case 1:
  n = 3;
  break;
 case 2:
  n = 5;
  break;
 case 3:
  n = 9;
  break;
 case 4:
  n = 17;
  break;
 default:
  n = 0;
 }
 return (n);
}