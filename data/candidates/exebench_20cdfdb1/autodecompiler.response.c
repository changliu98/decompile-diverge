void liefere_double_array_statistik(double array[], int laenge, double *min, double *max, double *summe, double *durchschnitt)
{
  int i;

  *min = array[0];
  *max = array[0];
  *summe = 0;

  for (i = 0; 1; i++)
  {
    if (i >= laenge)
      break;
    if (array[i] < *min)
      *min = array[i];
    if (array[i] > *max)
      *max = array[i];
    *summe += array[i];
  }

  *durchschnitt = (*summe / laenge) * 1.0;
}