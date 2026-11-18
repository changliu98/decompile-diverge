void liefere_double_array_statistik(const double array[], int laenge,
  double *min, double *max, double *summe, double *durchschnitt)
{
  *min = array[0];
  *max = array[0];
  *summe = 0;
  for (int i = 0; i < laenge; i++)
  {
    if (array[i] < *min)
      *min = array[i];
    if (array[i] > *max)
      *max = array[i];
    *summe += array[i];
  }
  *durchschnitt = (1.0 * *summe) / laenge;
}