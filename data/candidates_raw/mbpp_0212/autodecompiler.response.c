int answer(int n)
{
  int i;
  int answer = 0;

  for (i = 1; ; i++)
  {
    if (i > n)
      break;

    answer += i * i * i * i;
  }

  return answer;
}