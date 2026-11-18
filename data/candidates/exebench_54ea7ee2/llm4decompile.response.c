void BTIC2D_TransWHT_Vert8(int *iblk, int *oblk)
{
 int a0, a1, a2, a3, a4, a5, a6, a7;
 int b0, b1, b2, b3, b4, b5, b6, b7;
 int c0, c1, c2, c3, c4, c5, c6, c7;
 int d0, d1, d2, d3, d4, d5, d6, d7;
 int e0, e1, e2, e3, e4, e5, e6, e7;
 int f0, f1, f2, f3, f4, f5, f6, f7;
 int g0, g1, g2, g3, g4, g5, g6, g7;
 int h0, h1, h2, h3, h4, h5, h6, h7;

 a0=iblk[0]; a1=iblk[8]; a2=iblk[16]; a3=iblk[24];
 a4=iblk[32]; a5=iblk[40]; a6=iblk[48]; a7=iblk[56];

 b0=(a0+a4)>>1; b1=(a1+a5)>>1; b2=(a2+a6)>>1; b3=(a3+a7)>>1;
 b4=(b0+b2)>>1; b5=(b1+b3)>>1; b6=(b0-b2)>>1; b7=(b1-b3)>>1;

 c0=a0+b4; c1=a1+b5; c2=a2+b6; c3=a3+b7;
 c4=(c0+c2)>>1; c5=(c1+c3)>>1; c6=(c0-c2)>>1; c7=(c1-c3)>>1;

 d0=a4+b4; d1=a5+b5; d2=a6+b6; d3=a7+b7;
 d4=(d0+d2)>>1; d5=(d1+d3)>>1; d6=(d0-d2)>>1; d7=(d1-d3)>>1;

 e0=c0+c4; e1=c1+c5; e2=c2+c6; e3=c3+c7;
 e4=(e0+e2)>>1; e5=(e1+e3)>>1; e6=(e0-e2)>>1; e7=(e1-e3)>>1;

 f0=d0+c4; f1=d1+c5; f2=d2+c6; f3=d3+c7;
 f4=(f0+f2)>>1; f5=(f1+f3)>>1; f6=(f0-f2)>>1; f7=(f1-f3)>>1;

 g0=e0+f4; g1=e1+f5; g2=e2+f6; g3=e3+f7;
 g4=(g0+g2)>>1; g5=(g1+g3)>>1; g6=(g0-g2)>>1; g7=(g1-g3)>>1;

 h0=g0+g4; h1=g1+g5; h2=g2+g6; h3=g3+g7;
 h4=(h0+h2)>>1; h5=(h1+h3)>>1; h6=(h0-h2)>>1; h7=(h1-h3)>>1;

 oblk[0]=h0; oblk[8]=h1; oblk[16]=h2; oblk[24]=h3;
 oblk[32]=h4; oblk[40]=h5; oblk[48]=h6; oblk[56]=h7;
}