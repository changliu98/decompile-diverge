void shiftarray(int *a)
{
 int i;
 for(i=0;i<9;i++)
 {
  a[i]=a[i+1];
 }
 a[9]=-1;
}