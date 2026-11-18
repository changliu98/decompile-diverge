void P_stats(float *prcp,int *rain_hrs,int *conseq_hrs,int *st_hr,float *max_p,int *max_hr,int mo,
            int *pflag)

{
  int tmp_hrs;
  int i;
  int *max_hr_local;
  float *max_p_local;
  int *st_hr_local;
  int *conseq_hrs_local;
  int *rain_hrs_local;
  float *prcp_local;
  
  tmp_hrs = 0;
  *rain_hrs = 0;
  *max_hr = 0;
  *max_p = 0.0;
  *conseq_hrs = 0;
  *st_hr = 0;
  for (i = 0; i < 0x18; i = i + 1) {
    if ((0.0 < prcp[i]) && (*rain_hrs = *rain_hrs + 1, *max_p <= prcp[i] && prcp[i] != *max_p)) {
      *max_p = prcp[i];
      *max_hr = i;
    }
  }
  for (i = 0; i < 0x18; i = i + 1) {
    pflag[i] = 0;
    if (prcp[i] <= 0.0) {
      if (*conseq_hrs < tmp_hrs) {
        *conseq_hrs = tmp_hrs;
        *st_hr = i - *conseq_hrs;
        tmp_hrs = 0;
      }
    }
    else {
      tmp_hrs = tmp_hrs + 1;
      pflag[i] = 1;
    }
  }
  if (*conseq_hrs < tmp_hrs) {
    *conseq_hrs = tmp_hrs;
    *st_hr = i - *conseq_hrs;
  }
  return;
}