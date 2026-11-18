int libbf_is_composed_poweroftwo(unsigned number, int *shift1, int *shift2)
{
  int count = 0;
  int shift = 0;

  if (number == 0)
  {
    return 0;
  }

  if (shift1)
  {
    *shift1 = 0;
  }
  if (shift2)
  {
    *shift2 = 0;
  }

  while (number)
  {
    if (number & 1)
    {
      count++;
      if (count == 1)
      {
        if (shift1)
        {
          *shift1 = shift;
        }
      }
      else if (count == 2)
      {
        if (shift2)
        {
          *shift2 = shift;
        }
      }
      else
      {
        return 0;
      }
    }

    shift++;
    number >>= 1;
  }

  return 1;
}