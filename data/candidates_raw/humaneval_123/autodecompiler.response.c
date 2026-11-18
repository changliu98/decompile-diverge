void do_callatz(int n,int *arr,int *len)
{
 int cap = 10;
 *len = 1;
 arr[0] = 1;

 while(1)
 {
  if(n == 1)
   break;
  else
  {
   if(n%2 == 1)
   {
    if(*len >= cap)
    {
     cap *= 2;
     arr = (int*)realloc(arr,sizeof(int)*cap);
    }
    arr[(*len)++] = n;
    n = 3*n + 1;
   }
   else
    n /= 2;
  }
 }

 for(int i = 1;i < *len;i++)
 {
  int t = arr[i];
  int j = i-1;
  while(j >= 0 && arr[j] > t)
  {
   arr[j+1] = arr[j];
   j--;
  }
  arr[j+1] = t;
 }
}