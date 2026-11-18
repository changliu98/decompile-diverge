void __cdecl get_vector_modulo(int *v, const int *m)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 3; ++i )
  {
    v[i] %= m[i];
    if ( v[i] < 0 )
      v[i] += m[i];
  }
}