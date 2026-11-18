int is_power_of_two(unsigned int number, int *shift1, int *shift2)
{
  unsigned int numbera = number;
  int i = 0;
  int count = 0;
  if (number == 0)
    return 0;
  if (shift1 != ((void *)0))
    *shift1 = 0;
  if (shift2 != ((void *)0))
    *shift2 = 0;
  while (numbera > 0)
  {
    if (numbera & 1)
    {
      count++;
      if (count == 1)
      {
        if (shift1 != ((void *)0))
          *shift1 = i;
      }
      else if (count == 2)
      {
        if (shift2 != ((void *)0))
          *shift2 = i;
      }
      else
        return 0;
    }
    i++;
    numbera = numbera >> 1;
  }
  return 1;
}