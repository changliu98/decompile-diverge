void calcular_escala(double fmin, double fmax, double favg, double *m, double *b)
{
  if (fmin > (fmax * 1.2 + favg * -1.0)/0.2)
  {
    *m = favg * 0.2 / (fmax - favg);
    *b = (fmax * -1.2 + favg * 0.2) / (fmax - favg);
  }
  else if (fmin == favg)
  {
    *m = 1.0;
    *b = 0.0;
  }
  else
  {
    *m = favg / (favg - fmin);
    *b = (fmin * -1.0 * favg) / (favg - fmin);
  }
}