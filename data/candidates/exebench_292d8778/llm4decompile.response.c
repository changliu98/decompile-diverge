void
lib3ds_quat_copy(Lib3dsQuat c, Lib3dsQuat a)
{
  int i;

  for (i=0; i<4; ++i) {
    c[i]=a[i];
  }
}