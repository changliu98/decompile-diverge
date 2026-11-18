unsigned char gfmul(unsigned char a, unsigned char b){
 unsigned char p = 0;
 while(1){
  if(b == 0) return p;
  if(b & 1) p ^= a;
  a <<= 1; a ^= (a&0x80)?0x1d:0;
  b >>= 1;
 }
}