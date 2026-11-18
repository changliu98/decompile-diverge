void liefere_double_array_statistik
               (double *array,int laenge,double *min,double *max,double *summe,double *durchschnitt)

{
  int i;
  double *durchschnitt_local;
  double *summe_local;
  double *max_local;
  double *min_local;
  int laenge_local;
  double *array_local;
  
  *min = *array;
  *max = *array;
  *summe = 0.0;
  for (i = 0; i < laenge; i = i + 1) {
    if (array[i] < *min) {
      *min = array[i];
    }
    if (*max <= array[i] && array[i] != *max) {
      *max = array[i];
    }
    *summe = array[i] + *summe;
  }
  *durchschnitt = (DAT_00102008 * *summe) / (double)laenge;
  return;
}