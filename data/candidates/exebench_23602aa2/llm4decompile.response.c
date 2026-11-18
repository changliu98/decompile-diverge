void
lib3ds_quat_scalar(Lib3dsQuat c, float k)
{
  int i;

  for (i=0; i<4; ++i) {
    c[i] *= k;
  }
}