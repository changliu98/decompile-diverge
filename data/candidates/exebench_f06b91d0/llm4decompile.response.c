void add_vector(vector a, vector b, vector out) {
  int i;
  for (i = 0; i < 3; i++) {
    out[i] = a[i] + b[i];
  }
}