void SHUF(uchar *b,uchar *b2)

{
  uchar *b2_local;
  uchar *b_local;
  
  *b2 = b[8];
  b2[1] = b[0xb];
  b2[2] = b[0xc];
  b2[3] = b[0xf];
  b2[4] = b[2];
  b2[5] = b[1];
  b2[6] = b[6];
  b2[7] = b[5];
  b2[8] = b[10];
  b2[9] = b[9];
  b2[10] = b[0xe];
  b2[0xb] = b[0xd];
  b2[0xc] = *b;
  b2[0xd] = b[7];
  b2[0xe] = b[4];
  b2[0xf] = b[3];
  return;
}