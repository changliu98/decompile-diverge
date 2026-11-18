void count_down(int *counter,int *ghost_counter)

{
  int i;
  int *ghost_counter_local;
  int *counter_local;
  
  if (0 < *counter) {
    *counter = *counter + -1;
  }
  for (i = 0; i < 4; i = i + 1) {
    if (0 < ghost_counter[i]) {
      ghost_counter[i] = ghost_counter[i] + -1;
    }
  }
  return;
}