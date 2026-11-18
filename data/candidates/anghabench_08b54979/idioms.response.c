static unsigned int F(unsigned int b, unsigned int c, unsigned int d)
{
  return (d & b) | (c & ~d);
}