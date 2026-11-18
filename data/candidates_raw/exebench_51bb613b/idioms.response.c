static int rand48()
{
  static unsigned int next = 4357;
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}