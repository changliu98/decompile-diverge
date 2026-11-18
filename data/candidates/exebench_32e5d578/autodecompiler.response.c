void intToBin(int n, int bin[8])
{
 int mask = 0x80;
 int i = 0;

 while(1)
 {
  if(i >= 8) break;
  bin[i] = (n & mask) ? 1 : 0;
  n <<= 1;
  ++i;
 }
}