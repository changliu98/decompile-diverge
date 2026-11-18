void calcular_escala(double x, double xmax, double xmin, double *a, double *b) {
  if (x > (xmax - 1.2 * xmin) / 0.2) {
    *a = 0.2 * xmin / (xmax - xmin);
    *b = xmin * ((xmax - 1.2 * xmin) / (xmax - xmin));
  } else if (x == xmin) {
    *a = 1.0;
    *b = 0.0;
  } else {
    *a = xmin / (xmin - x);
    *b = -x * xmin / (xmin - x);
  }
}