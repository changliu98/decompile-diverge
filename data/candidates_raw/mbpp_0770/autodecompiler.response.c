int answer(int n)
{
  int i;
  int answer = 0;

  for (i = 1; ; i++)
  {
    int tmp = 2 * i - 1;
    if (i > n) break;
    answer += tmp * tmp * tmp * tmp;
  }

  return answer;
}