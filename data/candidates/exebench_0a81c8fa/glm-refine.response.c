void std::swap<unsigned short>(unsigned short *a, unsigned short *b)
{
  unsigned short temp = *a;
  *a = *b;
  *b = temp;
}