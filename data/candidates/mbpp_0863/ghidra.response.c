int func0(int *arr,int n)

{
  int iVar1;
  int *__ptr;
  int size_v;
  int *v;
  int temp;
  int j;
  int i;
  int count;
  int ans;
  int n_local;
  int *arr_local;
  
  ans = 0;
  count = 0;
  for (i = 0; i < n + -1; i = i + 1) {
    for (j = 0; j < (n - i) + -1; j = j + 1) {
      if (arr[j + 1] < arr[j]) {
        iVar1 = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = iVar1;
      }
    }
  }
  __ptr = malloc((long)n << 2);
  size_v = 1;
  *__ptr = *arr;
  for (i = 1; i < n; i = i + 1) {
    if (arr[i] != arr[i + -1]) {
      __ptr[size_v] = arr[i];
      size_v = size_v + 1;
    }
  }
  for (i = 0; i < size_v; i = i + 1) {
    if ((i < 1) || (__ptr[i] != __ptr[i + -1] + 1)) {
      count = 1;
    }
    else {
      count = count + 1;
    }
    if (ans < count) {
      ans = count;
    }
  }
  free(__ptr);
  return ans;
}