void count_down(int *lives, int ghost[5][2])
{
 if (*lives > 0)
 {
  *lives = *lives - 1;
 }
 int i = 0;
 while (i < 5)
 {
  if (ghost[i][0] > 0)
  {
   ghost[i][0] = ghost[i][0] - 1;
  }
  else
  {
   i++;
  }
 }
}