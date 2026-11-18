void compute_rain_stats(float *rainfall, int *wet_days, int *consec_wet,
                        int *peak_wet_day, float *highest_rainfall,
                        int *day_of_peak, int num_days, int pflag[])
{
   int i;
   int tmp_wet = 0;

   *wet_days = 0;
   *day_of_peak = 0;
   *highest_rainfall = 0.0;
   *consec_wet = 0;
   *peak_wet_day = 0;

   for (i = 0; i < 25; i++) {
      if (rainfall[i] > 0) {
         (*wet_days)++;
         if (rainfall[i] > *highest_rainfall) {
            *highest_rainfall = rainfall[i];
            *day_of_peak = i;
         }
      }
      else
         i = 25;
   }

   for (i = 0; i < 25; i++) {
      pflag[i] = 0;
      if (rainfall[i] > 0) {
         tmp_wet++;
         pflag[i] = 1;
      }
      else {
         if (tmp_wet > *consec_wet) {
            *consec_wet = tmp_wet;
            *peak_wet_day = i - *consec_wet;
            tmp_wet = 0;
         }
      }
   }
   if (tmp_wet > *consec_wet) {
      *consec_wet = tmp_wet;
      *peak_wet_day = i - *consec_wet;
   }
}