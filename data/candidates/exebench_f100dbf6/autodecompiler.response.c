void tea_decrypt(int* v, int* k)
{
 unsigned long y=v[0], z=v[1], sum=0xC6EF3720, i;
 unsigned long delta=0x9e3779b9;
 unsigned long a=k[0], b=k[1], c=k[2], d=k[3];
 for (i=0; i < 32; i++) {
  sum -= delta;
  y -= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
  z -= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);
 }
 v[0]=y; v[1]=z;
}