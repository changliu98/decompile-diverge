int func0(int *arr,int n)

{
  int iVar1;
  void *__ptr;
  int i_2;
  int j;
  int i_1;
  int i;
  int max;
  int *mls;
  int n_local;
  int *arr_local;
  
  __ptr = malloc((long)n << 2);
  max = 0;
  for (i = 0; i < n; i = i + 1) {
    *(undefined4 *)((long)__ptr + (long)i * 4) = 1;
  }
  for (i_1 = 0; i_1 < n; i_1 = i_1 + 1) {
    for (j = 0; j < i_1; j = j + 1) {
      iVar1 = abs(arr[i_1] - arr[j]);
      if ((iVar1 < 2) &&
         (*(int *)((long)__ptr + (long)i_1 * 4) < *(int *)((long)__ptr + (long)j * 4) + 1)) {
        *(int *)((long)__ptr + (long)i_1 * 4) = *(int *)((long)__ptr + (long)j * 4) + 1;
      }
    }
  }
  for (i_2 = 0; i_2 < n; i_2 = i_2 + 1) {
    if (max < *(int *)((long)__ptr + (long)i_2 * 4)) {
      max = *(int *)((long)__ptr + (long)i_2 * 4);
    }
  }
  free(__ptr);
  return max;
}