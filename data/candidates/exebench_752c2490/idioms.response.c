int valid(int *board, int n)
{
  int i;
  for (i = 0; i < n - 2; i++)
  {
    if (board[i] > 0)
    {
      board[i + 2] -= board[i] * 3;
      board[i + 1] -= board[i] * 2;
      board[i] = 0;
    }
    else if (board[i] < 0)
    {
      return 0;
    }
  }
  int valid = 1;
  if (board[n - 1] == 0)
  {
    if (board[n - 2] == 0)
    {
      valid = 0;
    }
  }
  return valid;
}