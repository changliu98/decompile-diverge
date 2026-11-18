int func0(int N, int K)
{
  int ret;

  if (N < K) {
    ret = -1;
  } else {
    int tmp_sum = 0;

    tmp_sum += ((N - K + 1) * (N - K + 2)) / 2;
    tmp_sum += ((N - 2 * K + 1) * (N - 2 * K + 2)) / 2;
    ret = tmp_sum;
  }

  return ret;
}