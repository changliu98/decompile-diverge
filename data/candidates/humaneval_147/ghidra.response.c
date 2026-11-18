int func0(int n)

{
  int iVar1;
  void *__ptr;
  long *__ptr_00;
  long *__ptr_01;
  void *pvVar2;
  long lVar3;
  int i_4;
  int result;
  int j_3;
  int i_3;
  int j_2;
  int j_1;
  int i_2;
  int times;
  int j;
  int i_1;
  int i;
  int **sum2;
  int **sum;
  int *a;
  int n_local;
  
  __ptr = malloc((long)n << 2);
  __ptr_00 = malloc((long)(n + 1) << 3);
  __ptr_01 = malloc((long)(n + 1) << 3);
  for (i = 0; i <= n; i = i + 1) {
    pvVar2 = calloc(3,4);
    __ptr_00[i] = (long)pvVar2;
    pvVar2 = calloc(3,4);
    __ptr_01[i] = (long)pvVar2;
  }
  *(undefined4 *)(*__ptr_00 + 8) = 0;
  *(undefined4 *)(*__ptr_00 + 4) = 0;
  *(undefined4 *)*__ptr_00 = 0;
  *(undefined4 *)(*__ptr_01 + 8) = 0;
  *(undefined4 *)(*__ptr_01 + 4) = 0;
  *(undefined4 *)*__ptr_01 = 0;
  for (i_1 = 1; i_1 <= n; i_1 = i_1 + 1) {
    *(int *)((long)__ptr + (long)(i_1 + -1) * 4) = ((i_1 * i_1 - i_1) + 1) % 3;
    for (j = 0; j < 3; j = j + 1) {
      *(undefined4 *)(__ptr_00[i_1] + (long)j * 4) =
           *(undefined4 *)(__ptr_00[i_1 + -1] + (long)j * 4);
    }
    lVar3 = (long)*(int *)((long)__ptr + (long)(i_1 + -1) * 4);
    *(int *)(__ptr_00[i_1] + lVar3 * 4) = *(int *)(__ptr_00[i_1] + lVar3 * 4) + 1;
  }
  for (times = 1; times < 3; times = times + 1) {
    for (i_2 = 1; i_2 <= n; i_2 = i_2 + 1) {
      for (j_1 = 0; j_1 < 3; j_1 = j_1 + 1) {
        *(undefined4 *)(__ptr_01[i_2] + (long)j_1 * 4) =
             *(undefined4 *)(__ptr_01[i_2 + -1] + (long)j_1 * 4);
      }
      if (0 < i_2) {
        for (j_2 = 0; j_2 < 3; j_2 = j_2 + 1) {
          lVar3 = (long)((*(int *)((long)__ptr + (long)(i_2 + -1) * 4) + j_2) % 3);
          *(int *)(__ptr_01[i_2] + lVar3 * 4) =
               *(int *)(__ptr_00[i_2 + -1] + (long)j_2 * 4) + *(int *)(__ptr_01[i_2] + lVar3 * 4);
        }
      }
    }
    for (i_3 = 0; i_3 <= n; i_3 = i_3 + 1) {
      for (j_3 = 0; j_3 < 3; j_3 = j_3 + 1) {
        *(undefined4 *)(__ptr_00[i_3] + (long)j_3 * 4) =
             *(undefined4 *)(__ptr_01[i_3] + (long)j_3 * 4);
        *(undefined4 *)(__ptr_01[i_3] + (long)j_3 * 4) = 0;
      }
    }
  }
  iVar1 = *(int *)__ptr_00[n];
  for (i_4 = 0; i_4 <= n; i_4 = i_4 + 1) {
    free((void *)__ptr_00[i_4]);
    free((void *)__ptr_01[i_4]);
  }
  free(__ptr_00);
  free(__ptr_01);
  free(__ptr);
  return iVar1;
}