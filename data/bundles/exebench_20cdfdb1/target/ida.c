void __cdecl liefere_double_array_statistik(
        const double *array,
        int laenge,
        double *min,
        double *max,
        double *summe,
        double *durchschnitt)
{
  int i; // [rsp+0h] [rbp-34h]

  *min = *array;
  *max = *array;
  *summe = 0.0;
  for ( i = 0; i < laenge; ++i )
  {
    if ( *min > array[i] )
      *min = array[i];
    if ( array[i] > *max )
      *max = array[i];
    *summe = array[i] + *summe;
  }
  *durchschnitt = 1.0 * *summe / (double)laenge;
}