static void TEA_transform(unsigned int buf[4], unsigned int const in[])
{
 __u32 sum = 0;
 __u32 b0 = buf[0], b1 = buf[1];
 __u32 a = in[0], b = in[1], c = in[2], d = in[3];
 int n = 16;

 do {
  sum += 0x9E3779B9;
  b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
  b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
 } while (--n);

 buf[0] += b0;
 buf[1] += b1;

}