int difference(int n,int m)
{
 int sum = sum_Odd(m) - sum_Odd(n-1);
 return sum;
}