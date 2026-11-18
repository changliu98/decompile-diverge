void noise_est(float noise_est_in, float *noise_est, float noise_est_inc,
               float noise_est_dec, float noise_est_min, float noise_est_max) {
  if (noise_est_in > (*noise_est + noise_est_inc))
    *noise_est += noise_est_inc;
  else if (noise_est_in < (*noise_est + noise_est_dec))
    *noise_est += noise_est_dec;
  else
    *noise_est = noise_est_in;
  if (*noise_est < noise_est_min) *noise_est = noise_est_min;
  if (*noise_est > noise_est_max) *noise_est = noise_est_max;
}