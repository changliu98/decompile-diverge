char *check_linear(int arr[], int len)
{
 char *result;
 int i, j, diff[len-1];
 for(j=1, i=0; j<len; j++, i++)
 {
  diff[i] = arr[j]-arr[i];
 }
 for(i=1; i<len-1; i++)
 {
  if(diff[i]!=diff[0])
  {
   result = "Non Linear Sequence";
   break;
  }
  else
  {
   result = "Linear Sequence";
  }
 }
 return result;
}