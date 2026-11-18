void sha1_transform(SHA1_CTX *ctx, const unsigned char data[])
{
   unsigned int i,j;
   unsigned int temp;
   unsigned int A,B,C,D,E,W[80];

   for (i=0,j=0; i < 16; ++i, j += 4)
      W[i] = ((unsigned int)data[j] << 24) + ((unsigned int)data[j+1] << 16) + ((unsigned int)data[j+2] << 8) + ((unsigned int)data[j+3]);
   for (i=16; i < 80; ++i)
   {
      W[i] = W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16];
      W[i] = (W[i] << 1) | (W[i] >> 31);
   }
   A = ctx->state[0];
   B = ctx->state[1];
   C = ctx->state[2];
   D = ctx->state[3];
   E = ctx->state[4];

   for (i=0; i < 20; ++i)
   {
      temp = ((A << 5) | (A >> (32-5))) + ((B & C) | (~B & D)) + E + W[i] + ctx->k[0];
      E = D;
      D = C;
      C = (B << 30) | (B >> (32-30));



      B = A;
      A = temp;
   }
   for (i=20; i < 40; ++i)
   {
      temp = ((A << 5) | (A >> (32-5))) + (B ^ C ^ D) + E + W[i] + ctx->k[1];
      E = D;
      D = C;
      C = (B << 30) | (B >> (32-30));
      B = A;
      A = temp;
   }
   for (i=40; i < 60; ++i)
   {
      temp = ((A << 5) | (A >> (32-5))) + ((B & C) | (B & D) | (C & D)) + E + W[i] + ctx->k[2];
      E = D;
      D = C;
      C = (B << 30) | (B >> (32-30));
      B = A;
      A = temp;
   }
   for (i=60; i < 80; ++i)
   {
      temp = ((A << 5) | (A >> (32-5))) + (B ^ C ^ D) + E + W[i] + ctx->k[3];
      E = D;
      D = C;
      C = (B << 30) | (B >> (32-30));
      B = A;
      A = temp;
   }

   ctx->state[0] += A;
   ctx->state[1] += B;
   ctx->state[2] += C;
   ctx->state[3] += D;
   ctx->state[4] += E;
}