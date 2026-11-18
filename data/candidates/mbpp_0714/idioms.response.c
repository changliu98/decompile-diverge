int func0(int n)
{
  int i;
  int na = n;
  int count = 0;
  for (i = 2; i * i <= n; i++) {
    int total = 0;
    while (na % i == 0) {
      na /= i;
      total++;
    }
    int temp = 0;
    for (int j = 1; j + temp <= total; j++) {
      temp += j;
      count++;
    }
  }
  if (na != 1)
    count++;
  return count;
}