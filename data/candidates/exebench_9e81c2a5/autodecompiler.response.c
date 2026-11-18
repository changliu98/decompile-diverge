void decipher(int *v, int *k)
{
 unsigned long y=v[0], z=v[1], sum=0x9E3779B9 * 32, i;
 unsigned long delta=0x9e3779b9;
 for(i=0; i<32; i++) {
  z-= ((y<<4) + (y>>5)) ^ (y + sum) ^ ((k[(sum>>11) & 3] + sum) ^ (z>>2));
  sum-=delta;
  y-= ((z<<4) + (z>>5)) ^ (z + sum) ^ ((k[sum & 3] + sum) ^ (y>>2));
 }
 v[0]=y; v[1]=z;
}