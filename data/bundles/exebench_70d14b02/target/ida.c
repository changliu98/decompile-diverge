void __cdecl lib3ds_vector_max(float *c, float *a)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 3; ++i )
  {
    if ( a[i] > c[i] )
      c[i] = a[i];
  }
}