unsigned __int16 calc_speed(unsigned __int16 *spds, int num, unsigned __int16 dflt)
{
  unsigned __int16 max_speed = 0;
  
  for (int i = 0; i < num; i++)
  {
    if (spds[i] > max_speed)
      max_speed = spds[i];
  }
  
  if (max_speed == 0)
    return dflt;
    
  return max_speed;
}