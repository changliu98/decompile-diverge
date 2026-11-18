static unsigned int f1(unsigned int b, unsigned int c, unsigned int d)
{
  return (d & b) | (c & ~d);
}