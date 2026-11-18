int func0(int *arr,int size)

{
  int i;
  int out;
  int size_local;
  int *arr_local;
  
  out = 0;
  for (i = 0; i < size / 2; i = i + 1) {
    if (arr[i] != arr[(size + -1) - i]) {
      out = out + 1;
    }
  }
  return out;
}