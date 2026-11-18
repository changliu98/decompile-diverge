int func0(int A[], int n)
{
 int maxsofar = 0, maxendinghere = 0;
 int i = 0;
 while (1) {
  if (i >= n)
   break;
  maxendinghere = ((maxendinghere + A[i]) < (0) ? (0) : (maxendinghere + A[i]));
  maxsofar = ((maxsofar) > (maxendinghere) ? (maxsofar) : (maxendinghere));
  ++i;
 }
 return maxsofar;
}