void sort(int *a,int n,int *b)
{
 int i;
 qsort(a,(size_t)n,sizeof(int),cmpfunc);
 for(i=0;i<n;i++)
 {
  b[i]=a[i];
 }
}