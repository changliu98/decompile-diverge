int func0(int *arr,int N,int K)

{
  int iVar1;
  undefined4 *__ptr;
  int local_30;
  int local_2c;
  int result;
  int i;
  int *dp;
  int K_local;
  int N_local;
  int *arr_local;
  
  qsort(arr,(long)N,4,cmpfunc);
  __ptr = malloc((long)N << 2);
  *__ptr = 0;
  for (i = 1; i < N; i = i + 1) {
    __ptr[i] = __ptr[i + -1];
    if (arr[i] - arr[i + -1] < K) {
      if (i < 2) {
        if (arr[i] + arr[i + -1] < (int)__ptr[i]) {
          local_30 = __ptr[i];
        }
        else {
          local_30 = arr[i] + arr[i + -1];
        }
        __ptr[i] = local_30;
      }
      else {
        if (__ptr[i + -2] + arr[i] + arr[i + -1] < (int)__ptr[i]) {
          local_2c = __ptr[i];
        }
        else {
          local_2c = __ptr[i + -2] + arr[i] + arr[i + -1];
        }
        __ptr[i] = local_2c;
      }
    }
  }
  iVar1 = __ptr[N + -1];
  free(__ptr);
  return iVar1;
}