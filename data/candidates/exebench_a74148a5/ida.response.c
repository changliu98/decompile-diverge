float __cdecl getUniform(int a, int c, int m, float *x)
{
  *x = (float)((float)((float)((float)a * *x) + (float)c)
             - (float)(m * (int)(float)((float)((float)((float)a * *x) + (float)c) / (float)m)))
     / (float)m;
  return *x;
}