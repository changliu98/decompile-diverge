unsigned_long_long func0(int n)

{
  unsigned_long_long uVar1;
  undefined8 *__ptr;
  void *pvVar2;
  int i_2;
  unsigned_long_long result;
  int j_1;
  int i_1;
  int j;
  int i;
  unsigned_long_long **bell;
  int n_local;
  
  __ptr = malloc((long)(n + 1) << 3);
  for (i = 0; i <= n; i = i + 1) {
    pvVar2 = malloc((long)(n + 1) << 3);
    __ptr[i] = pvVar2;
    for (j = 0; j <= n; j = j + 1) {
      *(undefined8 *)(__ptr[i] + (long)j * 8) = 0;
    }
  }
  *(undefined8 *)*__ptr = 1;
  for (i_1 = 1; i_1 <= n; i_1 = i_1 + 1) {
    *(undefined8 *)__ptr[i_1] = *(undefined8 *)(__ptr[i_1 + -1] + (long)(i_1 + -1) * 8);
    for (j_1 = 1; j_1 <= i_1; j_1 = j_1 + 1) {
      *(long *)(__ptr[i_1] + (long)j_1 * 8) =
           *(long *)(__ptr[i_1 + -1] + (long)(j_1 + -1) * 8) +
           *(long *)(__ptr[i_1] + (long)(j_1 + -1) * 8);
    }
  }
  uVar1 = *(unsigned_long_long *)__ptr[n];
  for (i_2 = 0; i_2 <= n; i_2 = i_2 + 1) {
    free((void *)__ptr[i_2]);
  }
  free(__ptr);
  return uVar1;
}