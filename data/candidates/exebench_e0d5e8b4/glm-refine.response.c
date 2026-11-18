void __cdecl dstsub4(int n, float *a)
{
  int half_n = n >> 1;

  if ( half_n == 2 )
  {
    float c1 = 0.38268343f * 0.70710677f;
    float c2 = 0.9238795f * 0.70710677f;
    float a1 = a[1];
    float a3 = a[3];

    // xr = -c1 * a[1] + c2 * a[3]
    float xr = c2 * a3 - c1 * a1;
    
    // a[3] = c1 * a[3] + c2 * a[1]
    a[3] = c1 * a3 + c2 * a1;
    
    a[1] = xr;
  }
  
  a[half_n] = 0.70710677f * a[half_n];
}