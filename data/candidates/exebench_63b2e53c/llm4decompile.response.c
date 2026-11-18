void count_down(int *counter, int ghost_counter[])
{
 if (*counter > 0)
  *counter -= 1;

 for (int i = 0; i < 4; i++)
  if (ghost_counter[i] > 0)
   ghost_counter[i] -= 1;
}