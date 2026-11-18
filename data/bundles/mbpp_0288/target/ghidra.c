int func0(int *arr,int N,int P)

{
  int i;
  int current_element;
  int P_local;
  int N_local;
  int *arr_local;
  
  current_element = 0;
  for (i = 0; i < N; i = i + 1) {
    if ((arr[i] * arr[i]) % P == 1) {
      current_element = current_element + 1;
    }
  }
  return current_element;
}