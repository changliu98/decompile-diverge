void nexper(int n, int a[], int mtc[], int even[])
{
  int i; int j; int k; int l; int m; int n1; int n2; int n3; int n4; int n5; int n6; int n7; int n8; int n9; int n10;
  int iab; int iaa; int iac; int iad;
  int s; int d;
  if (*mtc == 0)
  {
    for (i = 1; i <= n; i++)
    {
      a[i] = i;
    }
    *mtc = 1;
    *even = 1;
  }
  else
  {
    if (*even == 1)
    {
      iab = a[1];
      a[1] = a[2];
      a[2] = iab;
      *even = 0;
      if (a[n] == 1 && a[1] == n % 2 + 2)
      {
        if (n <= 3)
        {
          *mtc = 0;
        }
        else
        {
          for (i = 1; i <= n - 3; i++)
          {
            if (a[i + 1] != a[i] + 1)
            {
              return;
            }
          }
          *mtc = 0;
        }
      }
    }
    else
    {
      s = 0;
      for (i = 2; i <= n; i++)
      {
        iaa = a[i];
        ib = i - 1;
        for (j = 1, d = 0; j <= ib; j++)
        {
          if (a[j] > iaa)
          {
            d++;
          }
        }
        s += d;
        if (s % 2 * ib != d)
        {
          m = (n + 1) * (s + 1) % 2;
          for (j = 1; j <= ib; j++)
          {
            n1 = a[j] - iaa;
            n2 = a[j] - m;
            if ((n1 >= 0 && n2 < 0) || (n1 < 0 && n2 >= 0))
            {
              m = a[j];
              l = j;
            }
          }
          a[l] = iaa;
          a[i] = m;
          *even = 1;
          return;
        }
      }
      *mtc = 0;
    }
  }
}