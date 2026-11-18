void mult_big(unsigned int a,unsigned int b,unsigned int *hi,unsigned int *lo)
{
 unsigned int a0 = a & 0xffff;
 unsigned int a1 = (a>>16) & 0xffff;
 unsigned int b0 = b & 0xffff;
 unsigned int b1 = (b>>16) & 0xffff;
 unsigned int i0 = a0*b0;
 unsigned int i1 = a0*b1;
 unsigned int i2 = a1*b0;
 unsigned int i3 = a1*b1;
 unsigned int p1 = i1 + i2;
 unsigned int p0 = i0 + (p1<<16);
 *hi = i3 + (p1>>16) + (i0>>16) + (i2>>16) + (a1*b1);
 *lo = p0;
}