unsigned short BigUnsignedShort (short i)
{

 unsigned char b1,b2;

 b1 = i & 0xff;
 b2 = (i>>8) & 0xff;

 return (b1<<8) +b2;
}