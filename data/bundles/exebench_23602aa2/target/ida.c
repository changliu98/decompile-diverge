void __cdecl lib3ds_quat_scalar(float *c, float k)
{
  int i; // [rsp+0h] [rbp-10h]

  for ( i = 0; i < 4; ++i )
    c[i] = k * c[i];
}