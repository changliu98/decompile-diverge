int find_fact(int n)
{
 int fact;
 int i = 1;
 int j;
 int ret;

 fact = 1;
 for (i = 1; ; i++)
 {
  if (i >= n)
  {
   ret = i - 1;
   break;
  }
  fact *= i;
  if (fact % n == 0)
  {
   ret = i;
   break;
  }
 }
 return (ret);
}