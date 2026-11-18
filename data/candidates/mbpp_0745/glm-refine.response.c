void __cdecl func0(int startnum, int endnum, int *result, int *result_size)
{
  *result_size = 0;

  for (int num = startnum; num <= endnum; ++num)
  {
    bool is_self_dividing = true;

    // Extract and test each digit of the current number
    for (int temp = num; temp > 0; temp /= 10)
    {
      int digit = temp % 10;

      // A self-dividing number cannot contain '0', and must be divisible by the digit
      if (digit == 0 || (num % digit) != 0)
      {
        is_self_dividing = false;
        break;
      }
    }

    if (is_self_dividing)
    {
      result[(*result_size)++] = num;
    }
  }
}