void __cdecl mm_us(float m1[4][4], float m2[4][4], float mout[4][4])
{
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      float su = 0.0f;
      for (int k = 0; k < 4; ++k)
      {
        su += m1[i][k] * m2[k][j];
      }
      mout[i][j] = su;
    }
  }
}