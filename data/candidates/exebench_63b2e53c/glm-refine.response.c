void __cdecl count_down(int *counter, int *ghost_counter)
{
  // Decrement the primary counter if it is positive
  if (*counter > 0)
    --*counter;

  // Decrement up to 4 secondary "ghost" counters if they are positive
  for (int i = 0; i < 4; ++i)
  {
    if (ghost_counter[i] > 0)
      --ghost_counter[i];
  }
}