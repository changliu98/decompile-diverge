void __cdecl od_filter_dering_direction_offsets(int *offset, int dir, int bstride)
{
  // 'step' represents the distance multiplier (1, 2, and 3)
  for (int step = 1; step <= 3; ++step)
  {
    if (dir > 4)
    {
      // Calculate offsets for directions 5, 6, 7, and 8
      offset[step - 1] = step * (6 - dir) / 2 + bstride * step;
    }
    else
    {
      // Calculate offsets for directions 1, 2, 3, and 4
      offset[step - 1] = step + bstride * (step * (dir - 2) / 2);
    }
  }
}