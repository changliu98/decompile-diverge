void get_vector_modulo(int *vec, int *mod) {
  int i;
  for (i = 0; i < 3; i++) {
    vec[i] %= mod[i];
    if (vec[i] < 0) vec[i] += mod[i];
  }
}