void dec_counter(int *counter, int *ghost_counter){
  int i;
  if (counter[0] > 0)
    counter[0]--;
  for (i = 0; i < 4; i++)
    if (ghost_counter[i] > 0)
      ghost_counter[i]--;
}