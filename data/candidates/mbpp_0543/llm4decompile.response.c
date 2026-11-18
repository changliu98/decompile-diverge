int func0(long long int a, long long int b)
{
 int i;
 for (i = 0; (a + b) > 0; i++)
  a = (a + b) / 10;
 return i;
}