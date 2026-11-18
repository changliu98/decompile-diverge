void __cdecl P_stats(
        float *prcp,
        int *rain_hrs,
        int *conseq_hrs,
        int *st_hr,
        float *max_p,
        int *max_hr,
        int mo,
        int *pflag)
{
  int tmp_hrs; // [rsp+0h] [rbp-38h]
  int i; // [rsp+4h] [rbp-34h]
  int ia; // [rsp+4h] [rbp-34h]

  tmp_hrs = 0;
  *rain_hrs = 0;
  *max_hr = 0;
  *max_p = 0.0;
  *conseq_hrs = 0;
  *st_hr = 0;
  for ( i = 0; i < 24; ++i )
  {
    if ( prcp[i] > 0.0 )
    {
      ++*rain_hrs;
      if ( prcp[i] > *max_p )
      {
        *max_p = prcp[i];
        *max_hr = i;
      }
    }
  }
  for ( ia = 0; ia < 24; ++ia )
  {
    pflag[ia] = 0;
    if ( prcp[ia] <= 0.0 )
    {
      if ( tmp_hrs > *conseq_hrs )
      {
        *conseq_hrs = tmp_hrs;
        *st_hr = ia - *conseq_hrs;
        tmp_hrs = 0;
      }
    }
    else
    {
      ++tmp_hrs;
      pflag[ia] = 1;
    }
  }
  if ( tmp_hrs > *conseq_hrs )
  {
    *conseq_hrs = tmp_hrs;
    *st_hr = ia - *conseq_hrs;
  }
}