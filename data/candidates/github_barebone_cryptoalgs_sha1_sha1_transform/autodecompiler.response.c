void sha1_transform(unsigned int buf[5], unsigned char block[64])
{
 unsigned int X[16];
 unsigned int A, B, C, D, E;
 unsigned int t;
 unsigned int j;
 unsigned int i;

 for (i = 0, j = 0; ; i++, j += 4)
 {
  if (i < 16)
   X[i] = ((unsigned int)block[j]) << 24 +
          ((unsigned int)block[j + 1]) << 16 +
          ((unsigned int)block[j + 2]) << 8 +
          ((unsigned int)block[j + 3]);
  else
   break;
 }

 while (1)
 {
  if (i < 80)
  {
   X[i] = (((X[i - 3] ^ X[i - 8] ^ X[i - 14] ^ X[i - 16]) << 1) | ((X[i - 3] ^ X[i - 8] ^ X[i - 14] ^ X[i - 16]) >> 31));
   i++;
  }
  else
   break;
 }

 A = buf[0];
 B = buf[1];
 C = buf[2];
 D = buf[3];
 E = buf[4];

 for (i = 0; i < 20; i++)
 {
  t = ((A << 5) | (A >> 27)) + ((B & C) ^ (~B & D)) + E + 0x5a827999 + X[i];
  E = D;
  D = C;
  C = ((B << 30) | (B >> 2)) & 0xffffffff;
  B = A;
  A = t;
 }

 for (; i < 40; i++)
 {
  t = ((A << 5) | (A >> 27)) + ((B ^ C ^ D)) + E + 0x6ed9eba1 + X[i];
  E = D;
  D = C;
  C = ((B << 30) | (B >> 2)) & 0xffffffff;
  B = A;
  A = t;
 }

 for (; i < 60; i++)
 {
  t = ((A << 5) | (A >> 27)) + ((B & C) ^ (B & D) ^ (C & D)) + E + 0x8f1bbcdc + X[i];
  E = D;
  D = C;
  C = ((B << 30) | (B >> 2)) & 0xffffffff;
  B = A;
  A = t;
 }

 for (; i < 80; i++)
 {
  t = ((A << 5) | (A >> 27)) + ((B ^ C ^ D)) + E + 0xca62c1d6 + X[i];
  E = D;
  D = C;
  C = ((B << 30) | (B >> 2)) & 0xffffffff;
  B = A;
  A = t;
 }

 buf[0] += A;
 buf[1] += B;
 buf[2] += C;
 buf[3] += D;
 buf[4] += E;
}