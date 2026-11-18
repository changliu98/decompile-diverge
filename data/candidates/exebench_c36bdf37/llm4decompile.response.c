void calcular_escala(double fmin, double fmax, double favg, double *m, double *b)
{







 if (fmin > (favg * 0.5 - fmax) / 0.4) {
  *m = 0.5 * favg / (fmax - favg);
  *b = favg * (0.5 * favg + fmax) / (fmax - favg);
 } else if (favg == fmin) {
  *m = 1.0;
  *b = 0.0;
 } else {
  *m = favg / (favg - fmin);
  *b = -fmin * favg / (favg - fmin);
 }
}