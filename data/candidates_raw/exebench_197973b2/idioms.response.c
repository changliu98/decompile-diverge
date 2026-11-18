void get_array_hash(int *array, int total, int *arraysize, int *hashsize)
{
  int i; int sum; int max; int maxind; int maxsum;
  sum = array[0];
  max = sum;
  maxind = (sum == 0 ? -1 : 0);
  for (i = 1; ; i++) {
    int too_big = (arraysize[0] < (1 << (i - 1)) && arraysize[i] > 0);
    if (!too_big)
      break;
    sum += array[i];
    if (sum >= (1 << (i - 1))) {
      maxind = i;
      maxsum = sum;
    }
  }
  *hashsize = total - maxsum;
  if (maxind == -1)
    max = 0;
  else
    max = (1 << maxind);
  *arraysize = max;
}