int func0(int n)
{
 int i, sum, temp;
 if(n <= 1) return 1;
 else {
  sum = 0;
  for(i = 0; i < n; ++i){
   temp = func0(i) * func0(n-i-1);
   sum += temp;
  }
  return sum;
 }
}