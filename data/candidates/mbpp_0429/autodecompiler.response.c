void
func0 (int *t1, int *t2, int *result, int len)
{
  int i;
  for (i = 0; i < len; i++)
    result[i] = t1[i] & t2[i];
}