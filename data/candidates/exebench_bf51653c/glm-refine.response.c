void __cdecl upzero(int dlt, int *dlti, int *bli)
{
  // Update the predictor coefficients (bli) based on the current quantized difference (dlt)
  if (dlt != 0)
  {
    for (int i = 0; i < 6; ++i)
    {
      // Determine if the sign of the past difference matches the current difference
      int wd2 = (dlti[i] * (long long)dlt < 0) ? -128 : 128;
      
      // Leak the coefficient by a factor of 255/256 and add the new adaptation step
      bli[i] = (int)((255LL * bli[i]) >> 8) + wd2;
    }
  }
  else
  {
    // If there is no difference, just leak the coefficients towards zero
    for (int i = 0; i < 6; ++i)
    {
      bli[i] = (int)((255LL * bli[i]) >> 8);
    }
  }

  // Shift the history buffer (dlti) to make room for the new difference
  // Note: dlti[2] is implicitly preserved by the original assembly/decompilation
  dlti[5] = dlti[4];
  dlti[4] = dlti[3];
  dlti[3] = dlti[2];
  dlti[1] = dlti[0];
  dlti[0] = dlt;
}