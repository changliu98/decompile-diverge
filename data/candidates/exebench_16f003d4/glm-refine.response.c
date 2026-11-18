void __cdecl calc_speed(double *pos_prev, double *pos_mid, double *pos_next, double dt)
{
  for (int j = 0; j <= 18; j += 6)
  {
    for (int i = 0; i < 3; ++i)
    {
      int idx = i + j;
      double avg = (pos_next[idx] + pos_prev[idx]) / 2.0 - pos_mid[idx];
      double diff = (pos_next[idx] - pos_prev[idx]) / 2.0;
      
      // Store the calculated speed/acceleration 3 elements ahead
      pos_mid[idx + 3] = (2.0 * avg + diff) / dt;
    }
  }
}