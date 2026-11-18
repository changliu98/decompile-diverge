void noise_est(float gain,float *noise_gain,float up,float down,float min,float max)

{
  float max_local;
  float min_local;
  float down_local;
  float up_local;
  float *noise_gain_local;
  float gain_local;
  
  if (gain <= *noise_gain + up) {
    if (*noise_gain + down <= gain) {
      *noise_gain = gain;
    }
    else {
      *noise_gain = *noise_gain + down;
    }
  }
  else {
    *noise_gain = *noise_gain + up;
  }
  if (*noise_gain < min) {
    *noise_gain = min;
  }
  if (max < *noise_gain) {
    *noise_gain = max;
  }
  return;
}