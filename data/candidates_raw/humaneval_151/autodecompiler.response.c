unsigned long ex2 (float *input, int length)
{
  unsigned long result = 0;
  int i = 0;

  while (1) {
    if (i < length) {
      if ((fabs (input[i] - round (input[i])) < 0.0001) && (input[i] > 0) && ((int)round (input[i]) % 2 == 1)) {
        result += (int)round (input[i]) * (int)round (input[i]);
      }
      i++;
    } else {
      break;
    }
  }

  return result;
}