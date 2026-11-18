void
lib3ds_vector_max(Lib3dsVector c, Lib3dsVector a)
{
  int i;

  for (i=0; i<3; ++i) {
    if (a[i] > c[i]) {
      c[i] = a[i];
    }
  }
}