void merge(int a[], int b[], int c[])
{
  int i = 0; int j = 0; int k = 0;
  while ( (i < 6) && (j < 6) )
    c[k++] = (a[i] < b[j]) ? a[i++] : b[j++];
  while ( i < 6 )
    c[k++] = a[i++];
  while ( j < 6 )
    c[k++] = b[j++];
}