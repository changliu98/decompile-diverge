void __cdecl kf_factor(int n, int *facbuf)
{
  int na = n;
  int p = 4;
  double floor_sqrt = floor(sqrt((double)n));

  do
  {
    // Find the next prime factor of 'na'
    while (na % p != 0)
    {
      // Cycle through potential factors: 4 -> 2 -> 3 -> 5 -> 7 -> 9 ...
      if (p == 2)
      {
        p = 3;
      }
      else if (p == 4)
      {
        p = 2;
      }
      else
      {
        p += 2;
      }

      // If the trial factor exceeds the square root, 'na' itself is prime
      if ((double)p > floor_sqrt)
      {
        p = na;
        break;
      }
    }

    // Divide out the found factor
    na /= p;

    // Store the factor and the remaining quotient in the buffer
    facbuf[0] = p;
    facbuf[1] = na;
    facbuf += 2;
  }
  while (na > 1);
}