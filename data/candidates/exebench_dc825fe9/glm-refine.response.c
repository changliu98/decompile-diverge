void __cdecl summary(int *arr, int len, double *pos_count, double *neg_count, double *zero_count)
{
  int pos_c = 0;
  int neg_c = 0;
  int zero_c = 0;

  for (int i = 0; i < len; ++i)
  {
    if (arr[i] > 0)
    {
      ++pos_c;
    }
    else if (arr[i] < 0)
    {
      ++neg_c;
    }
    else
    {
      ++zero_c;
    }
  }

  double d_len = (double)len;
  *pos_count = (double)pos_c / d_len;
  *neg_count = (double)neg_c / d_len;
  *zero_count = (double)zero_c / d_len;
}