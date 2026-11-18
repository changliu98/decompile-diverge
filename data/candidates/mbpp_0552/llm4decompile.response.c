char* func0(int seq_nums[], int n)
{
 int diff[n-1];

 for(int i=1;i<n;i++)
 {
  diff[i-1]=seq_nums[i]-seq_nums[i-1];
 }

 for(int i=1;i<n-1;i++)
 {
  if(diff[i]!=diff[0])
  {
   return "Non Linear Sequence";
  }
 }

 return "Linear Sequence";
}