_Bool func0(int *A,int arr_size,int sum,int *triplet)

{
  int iVar1;
  int k;
  int j;
  int i;
  int *triplet_local;
  int sum_local;
  int arr_size_local;
  int *A_local;
  
  i = 0;
  do {
    iVar1 = i;
    if (arr_size + -2 <= i) {
      return false;
    }
    while (j = iVar1 + 1, j < arr_size + -1) {
      for (k = iVar1 + 2; iVar1 = j, k < arr_size; k = k + 1) {
        if (A[i] + A[j] + A[k] == sum) {
          *triplet = A[i];
          triplet[1] = A[j];
          triplet[2] = A[k];
          return true;
        }
      }
    }
    i = i + 1;
  } while( true );
}