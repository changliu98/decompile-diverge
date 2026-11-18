bool is_empty(float *spectrum, int N)
{
  for (int k = 0; k < N; ++k)
  {
    if (spectrum[k] > FLT_MIN)
      return false;
  }
  return true;
}