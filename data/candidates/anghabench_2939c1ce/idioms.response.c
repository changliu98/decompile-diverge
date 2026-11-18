void swapIntEndian(int *word)
{
  char a;
  a = *word;
  *word = *(word + 3);
  *(word + 3) = a;
  a = *(word + 1);
  *(word + 1) = *(word + 2);
  *(word + 2) = a;
}