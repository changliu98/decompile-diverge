void lib3ds_vector_copy(float a[3], float b[3]) {
  int i;
  for (i = 0; i < 3; i++) {
    a[i] = b[i];
  }
}