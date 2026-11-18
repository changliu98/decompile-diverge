int set_bit(int *word, int n)
{
  int mask = 1 << n;
  *word = *word | mask;
  return *word;
}