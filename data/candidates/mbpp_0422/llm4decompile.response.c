double func0(int n)
{
 double sum = 0.0;
 for (int i = 1; i <= n; i++)
  sum += i * i * i;
 double avg = sum / n;
 avg = round(avg * 1000000000000000.0) / 1000000000000000.0;
 return avg;
}