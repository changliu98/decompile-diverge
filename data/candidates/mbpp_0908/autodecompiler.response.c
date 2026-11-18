int func0()
{
 int n , m;
 scanf__bench("%d" , &n);
 int S[n];
 for(m = 0 ; m < n ; m++)
 {
  S[m] = m;
 }
 int p , q , k;
 char str[100];
 while(scanf__bench("%s" , str) , strcmp__bench(str , "quit") != 0)
 {
  sscanf__bench(str , "%d %d" , &p , &q);
  if(p < 0 || p > n - 1 || q < 0 || q > n - 1)
  {
   printf__bench("Illegal pair of sites\n");
   continue;
  }
  if(S[p] == S[q])
   printf__bench("Connected\n");
  else
  {
   for(k = 0 ; k < n ; k++)
   {
    if(S[k] == S[q])
     S[k] = S[p];
   }
  }
 }
 return 0;
}