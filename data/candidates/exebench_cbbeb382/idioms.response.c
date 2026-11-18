int factors(int n, int *arr)
{
  int i = 0;
  while (n % 53 == 0)
  {
    n /= 53;
    arr[i] = 53;
    i++;
  }
  while (n % 47 == 0)
  {
    n /= 47;
    arr[i] = 47;
    i++;
  }
  while (n % 43 == 0)
  {
    n /= 43;
    arr[i] = 43;
    i++;
  }
  while (n % 41 == 0)
  {
    n /= 41;
    arr[i] = 41;
    i++;
  }
  while (n % 37 == 0)
  {
    n /= 37;
    arr[i] = 37;
    i++;
  }
  while (n % 31 == 0)
  {
    n /= 31;
    arr[i] = 31;
    i++;
  }
  while (n % 29 == 0)
  {
    n /= 29;
    arr[i] = 29;
    i++;
  }
  while (n % 23 == 0)
  {
    n /= 23;
    arr[i] = 23;
    i++;
  }
  while (n % 19 == 0)
  {
    n /= 19;
    arr[i] = 19;
    i++;
  }
  while (n % 17 == 0)
  {
    n /= 17;
    arr[i] = 17;
    i++;
  }
  while (n % 13 == 0)
  {
    n /= 13;
    arr[i] = 13;
    i++;
  }
  while (n % 11 == 0)
  {
    n /= 11;
    arr[i] = 11;
    i++;
  }
  while (n % 8 == 0)
  {
    n /= 8;
    arr[i] = 8;
    i++;
  }
  while (n % 7 == 0)
  {
    n /= 7;
    arr[i] = 7;
    i++;
  }
  while (n % 5 == 0)
  {
    n /= 5;
    arr[i] = 5;
    i++;
  }
  while (n % 4 == 0)
  {
    n /= 4;
    arr[i] = 4;
    i++;
  }
  while (n % 3 == 0)
  {
    n /= 3;
    arr[i] = 3;
    i++;
  }
  while (n % 2 == 0)
  {
    n /= 2;
    arr[i] = 2;
    i++;
  }
  if (n > 31)
  {
    int num = 2;
    int m1 = 0;
    int m2 = 0;
    while (n > 1)
    {
      m1 = 6 * num - 1;
      m2 = 6 * num + 1;
      while (n % m1 == 0)
      {
        arr[i] = m1;
        i++;
        n /= m1;
      }
      while (n % m2 == 0)
      {
        arr[i] = m2;
        i++;
        n /= m2;
      }
      num++;
    }
  }
  return i;
}