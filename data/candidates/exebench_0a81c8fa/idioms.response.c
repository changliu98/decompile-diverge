void SWAP_short(void *a, void *b)
{
  void *temp = a;
  a = b;
  b = temp;
}