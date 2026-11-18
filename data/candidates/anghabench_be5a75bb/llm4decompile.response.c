int frag_num(int i)
{
  return 3 - (i % 4) + ((i / 4) * 4);
}