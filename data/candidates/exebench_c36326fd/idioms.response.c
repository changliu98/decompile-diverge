void initialize_temp(int *from, int *to)
{
  int i = 9;
  int j = 14;
  for ( ; i >= 0; i--)
    to[j--] = from[i];
  for ( ; j != -1; j--)
    to[j] = 0;
}