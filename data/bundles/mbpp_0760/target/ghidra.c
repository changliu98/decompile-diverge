char * func0(int *arr,int n)

{
  int i;
  int n_local;
  int *arr_local;
  
  i = 1;
  while( true ) {
    if (n <= i) {
      return "YES";
    }
    if (arr[i] != *arr) break;
    i = i + 1;
  }
  return "NO";
}