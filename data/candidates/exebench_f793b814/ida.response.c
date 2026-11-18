void __cdecl TEA_transform(unsigned int *buf, const unsigned int *in)
{
  int n; // [rsp+0h] [rbp-30h]
  __u32 b1; // [rsp+14h] [rbp-1Ch]
  unsigned int b0; // [rsp+18h] [rbp-18h]
  __u32 sum; // [rsp+1Ch] [rbp-14h]

  sum = 0;
  b0 = *buf;
  b1 = buf[1];
  n = 16;
  do
  {
    sum -= 1640531527;
    b0 += (in[1] + (b1 >> 5)) ^ (sum + b1) ^ (*in + 16 * b1);
    b1 += (in[3] + (b0 >> 5)) ^ (sum + b0) ^ (in[2] + 16 * b0);
    --n;
  }
  while ( n );
  *buf += b0;
  buf[1] += b1;
}