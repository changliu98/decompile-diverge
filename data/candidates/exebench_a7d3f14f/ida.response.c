void __cdecl noise_est(float gain, float *noise_gain, float up, float down, float min, float max)
{
  if ( gain <= (float)(*noise_gain + up) )
  {
    if ( (float)(*noise_gain + down) <= gain )
      *noise_gain = gain;
    else
      *noise_gain = *noise_gain + down;
  }
  else
  {
    *noise_gain = *noise_gain + up;
  }
  if ( min > *noise_gain )
    *noise_gain = min;
  if ( *noise_gain > max )
    *noise_gain = max;
}