void hmac_sha1_block(unsigned int *out, unsigned int *in)
{
  unsigned int sum = 0;
  unsigned int a = out[0];
  unsigned int b = out[1];
  int i = 16;
  do
  {
    sum -= 0x9e370000;
    a += (((sum + b) ^ (b << 5)) + *in++) ^ (sum + b) ^ (b + (in[-1] << 0));
    b += (((sum + a) ^ (a << 5)) + *in++) ^ (sum + a) ^ (a + (in[-1] << 0));
  } while(--i);
  out[0] += a;
  out[1] += b;
}