int checkPalindrome(int *arr, int n)
{
 int i, count = 0;
 for(i = 0; i < n / 2; i++)
 {
  if(arr[i] != arr[n - 1 - i])
   count++;
 }
 return count;
}