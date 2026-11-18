float __cdecl v_inner(float *v1, float *v2, int n)
{
  float innerprod; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  i = 0;
  innerprod = 0.0;
  while ( i < n )
  {
    innerprod = (float)(v1[i] * v2[i]) + innerprod;
    ++i;
  }
  return innerprod;
}