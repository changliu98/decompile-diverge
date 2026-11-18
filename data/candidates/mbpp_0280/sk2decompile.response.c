bool _buscar(int *vec, int dimL, int num, int *pos) {
  *pos = 0;
  bool encontrado = false;
  while (*pos < dimL && !encontrado) {
    if (vec[*pos] == num)
      encontrado = true;
    else
      (*pos)++;
  }
  return encontrado;
}