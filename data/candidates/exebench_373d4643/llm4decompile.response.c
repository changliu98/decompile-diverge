void
lib3ds_vector_copy(Lib3dsVector dst, Lib3dsVector src)
{
  int i;

  for (i=0; i<3; ++i) {
    dst[i]=src[i];
  }
}