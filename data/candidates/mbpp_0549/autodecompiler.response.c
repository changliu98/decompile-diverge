int func0(int n)
{
  int i;
  int answer = 0;

  int tmp = 0;

  for (i = 1; ; i++)
  {
    if (i > n)
      break;

    tmp = 2*i - 1;

    answer += tmp * tmp * tmp * tmp * tmp;
  }

  return answer;
}