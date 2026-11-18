void __cdecl merge(int *a, int *b, int *c)
{
  int i = 0;
  int j = 0;
  int k = 0;

  // Merge elements from both arrays until one is exhausted
  while ( i < 6 && j < 6 )
  {
    if ( a[i] >= b[j] )
      c[k++] = b[j++];
    else
      c[k++] = a[i++];
  }

  // Append any remaining elements from array 'a'
  while ( i < 6 )
    c[k++] = a[i++];

  // Append any remaining elements from array 'b'
  while ( j < 6 )
    c[k++] = b[j++];
}