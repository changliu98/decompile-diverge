int matM4toM3(double *m4, double *m3)
{
  m3[0] = m4[0];
  m3[1] = m4[1];
  m3[2] = m4[2];
  m3[3] = m4[4];
  m3[4] = m4[5];
  m3[5] = m4[6];
  m3[6] = m4[8];
  m3[7] = m4[8];
  m3[8] = m4[10];
  return 0;
}