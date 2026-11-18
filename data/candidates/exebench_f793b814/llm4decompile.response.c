void TEA_transform(uint32_t *buf, uint32_t *in)
{
 uint32_t y, z, sum = 0, delta = 0x9e3779b9;
 uint32_t *k;

 y = buf[0];
 z = buf[1];

 k = in;


 for (int i = 0; i < 16; i++) {
  sum += delta;
  y +=
      (z << 4) + (k[0] ^ (z + sum)) ^ (z + (k[1] >> 5));
  z +=
      (y << 4) + (k[2] ^ (y + sum)) ^ (y + (k[3] >> 5));
  k += 4;
 }

 buf[0] += y;
 buf[1] += z;
}