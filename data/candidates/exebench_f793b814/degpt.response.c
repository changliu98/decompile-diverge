void TEA_transform(uint *buf,uint *in)

{
  int n;
  __u32 d;
  __u32 c;
  __u32 b;
  __u32 a;
  __u32 b1;
  __u32 b0;
  __u32 sum;
  uint *in_local;
  uint *buf_local;
  
  sum = 0;
  b0 = *buf;
  b1 = buf[1];
  n = 0x10;
  do {
    sum = sum + 0x9e3779b9;
    b0 = (b1 * 0x10 + *in ^ b1 + sum ^ (b1 >> 5) + in[1]) + b0;
    b1 = (b0 * 0x10 + in[2] ^ b0 + sum ^ (b0 >> 5) + in[3]) + b1;
    n = n + -1;
  } while (n != 0);
  *buf = b0 + *buf;
  buf[1] = b1 + buf[1];
  return;
}