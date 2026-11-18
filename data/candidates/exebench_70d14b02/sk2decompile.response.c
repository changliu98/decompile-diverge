void lib3ds_vector_max(float a[3], float b[3]) {
  int i;
  for (i = 0; i < 3; i++) {
    if (b[i] > a[i]) {
      a[i] = b[i];
    }
  }
}