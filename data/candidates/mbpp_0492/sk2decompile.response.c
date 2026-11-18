int _busqueda_binaria(int *a, int n, int x) {
  int izq = 0;
  int der = n - 1;
  int encontrado = 0;
  int medio;
  while (izq <= der && !encontrado) {
    medio = (der + izq) / 2;
    if (a[medio] == x) {
      encontrado = 1;
    } else if (a[medio] > x) {
      der = medio - 1;
    } else {
      izq = medio + 1;
    }
  }
  return encontrado;
}