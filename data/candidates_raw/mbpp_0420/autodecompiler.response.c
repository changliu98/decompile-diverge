int answer(int n)
{
  int i;
  int answer = 0;

  for (i = 1; ; i++)
  {
    if (i > n)
      break;

    answer += (2*i) * (2*i) * (2*i);
  }

  return answer;
}