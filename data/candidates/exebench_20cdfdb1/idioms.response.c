void liefere_double_array_statistik(double *array, int laenge, double *min, double *max, double *summe, double *durchschnitt)
{
  int i;
  *min = array[0];
  *max = array[0];
  *summe = 0.0;
  for (i = 0; i < laenge; i++) {
    if (*min > array[i])
      *min = array[i];
    if (array[i] > *max)
      *max = array[i];
    *summe += array[i];
  }
  *durchschnitt = (double)(*summe * 1.0 / (double)laenge);
  return;
}