void tea_decode(int* v,int* k)
{
 unsigned long y=v[0],z=v[1], sum,
  delta=0x9e3779b9, n=32;
 unsigned long a=k[0],b=k[1],c=k[2],d=k[3];
 sum=delta<<5 ;
 for (n=0; n < 32; ++n) {
  z-= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);
  y-= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
  sum-=delta ; }
 v[0]=y ; v[1]=z ;
}