void stbi__idct_block(stbi_uc *out, int out_stride, short *data)
{
   int i,j;
   int y;
   int x;
   int z;
   int a,b,c,d,e,f,g,h;
   int tmp[64];
   int p1,p2,p3,p4,p5,p6,p7,p8;
   int t0,t1,t2,t3,t4,t5,t6,t7;
   int v0,v1,v2,v3,v4,v5,v6,v7;


   for (y=0; y < 8; ++y) {
      for (x=0; x < 8; ++x) {
         p1 = data[x+0] + data[x+8];
         p2 = data[x+0] - data[x+8];
         p3 = data[x+2] + data[x+6];
         p4 = data[x+2] - data[x+6];
         p5 = data[x+4] + data[x+2];
         p6 = data[x+4] - data[x+2];
         p7 = data[x+6] + data[x+4];
         p8 = data[x+6] - data[x+4];

         z = (p1+p5)*20531 + p1*12299 + p5*20531 + 16384;
         tmp[y*8+x] = (z + p3*26722 + p7*12299) >> 15;

         t0 = p2*29692 + p2*20531 + p3*25172 + p4*12299 + p5*25172 + p6*29692 + p7*20531 + p8*29692 + 2097152;
         t1 = p2*25172 - p2*29692 - p3*12299 + p4*29692 - p5*12299 - p6*25172 + p7*12299 - p8*25172 + 2097152;
         t2 = p2*20531 - p2*12299 - p3*29692 - p4*20531 + p5*29692 + p6*12299 + p7*29692 + p8*12299 + 2097152;
         t3 = p2*12299 - p2*20531 + p3*12299 - p4*29692 + p5*20531 - p6*29692 + p7*20531 - p8*12299 + 2097152;

         v0 = tmp[y*8+x] + t3;
         v1 = tmp[y*8+x] - t3;
         v2 = tmp[y*8+x] + t1;
         v3 = tmp[y*8+x] - t1;
         v4 = tmp[y*8+x] + t2;
         v5 = tmp[y*8+x] - t2;
         v6 = tmp[y*8+x] + t0;
         v7 = tmp[y*8+x] - t0;

         tmp[y*8+x] = ((v4+v5) + (v6+v7)) >> 10;
         tmp[y*8+7-(x)] = ((v4-v5) + (v6-v7)) >> 10;
         tmp[y*8+x+56] = ((v4+v5) - (v6+v7)) >> 10;
         tmp[y*8+7-(x)+56] = ((v4-v5) - (v