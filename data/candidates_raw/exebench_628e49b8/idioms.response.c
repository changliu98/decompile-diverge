void add(float a[16], float b[16], float result[16])
{
  unsigned int i;
  for (i = 0; i < 16; i++)
    result[i] = a[i] + b[i];
}