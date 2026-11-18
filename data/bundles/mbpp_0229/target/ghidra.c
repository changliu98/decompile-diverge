_Bool func0(int *arr1,int *arr2,int n)

{
  int i;
  int n_local;
  int *arr2_local;
  int *arr1_local;
  
  i = 0;
  while( true ) {
    if (n <= i) {
      return true;
    }
    if (arr1[i] != arr2[i]) break;
    i = i + 1;
  }
  return false;
}