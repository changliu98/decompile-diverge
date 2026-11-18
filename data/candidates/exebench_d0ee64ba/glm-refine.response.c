void __cdecl simplify(int *numerator, int *denominator)
{
  int num = *numerator;
  int den = *denominator;
  int commonNum;
  int lowestNum;

  // Determine the starting point for the GCD search.
  // The original logic effectively selects the minimum of the absolute values,
  // with a fallback to the numerator if the denominator is zero or negative.
  if (den > 0 && num > 0 && num < den)
    lowestNum = num;
  else if (den <= 0)
    lowestNum = num;
  else
    lowestNum = den;

  // Search for the greatest common divisor (GCD).
  // Note: This preserves the original behavior where the search steps away from zero
  // (e.g., decrementing if positive, incrementing if negative) until it finds a 
  // common divisor or reaches zero.
  while (lowestNum != 0)
  {
    if (num % lowestNum == 0 && den % lowestNum == 0)
    {
      commonNum = lowestNum;
      break;
    }
    if (lowestNum > 0)
      lowestNum--;
    else
      lowestNum++;
  }

  // The original code had a specific check to prevent division by -1.
  if (commonNum == -1)
    commonNum = 1;

  *numerator = num / commonNum;
  *denominator = den / commonNum;
}