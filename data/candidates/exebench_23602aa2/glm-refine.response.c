void __cdecl lib3ds_quat_scalar(float *c, float k)
{
  for (int i = 0; i < 4; ++i)
    c[i] *= k;
}