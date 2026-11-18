char* func0(int arr[], int n, int p)
{
 int sum = 0;
 for(int i = 0; i < n; i++)
  sum += arr[i];

 if(p == 1)
 {
  if(sum % 2 == 0)
   return "ODD";
  else
   return "EVEN";
 }
 else
 {
  if(sum % 2 == 0)
   return "EVEN";
  else
   return "ODD";
 }
}