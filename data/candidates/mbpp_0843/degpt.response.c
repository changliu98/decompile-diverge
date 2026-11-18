longlong func0(int n,int *primes,int primesSize)

{
  int iVar1;
  longlong lVar2;
  undefined8 *__ptr;
  void *__ptr_00;
  longlong *__ptr_01;
  int iVar3;
  longlong result;
  longlong next_ugly;
  int j;
  int i;
  longlong *values;
  int *indices;
  longlong *uglies;
  int primesSize_local;
  int *primes_local;
  int n_local;
  
  __ptr = malloc((long)n << 3);
  __ptr_00 = calloc((long)primesSize,4);
  __ptr_01 = malloc((long)primesSize << 3);
  *__ptr = 1;
  for (i = 0; i < primesSize; i = i + 1) {
    __ptr_01[i] = (long)primes[i];
  }
  for (i = 1; i < n; i = i + 1) {
    next_ugly = *__ptr_01;
    for (j = 1; j < primesSize; j = j + 1) {
      if (__ptr_01[j] < next_ugly) {
        next_ugly = __ptr_01[j];
      }
    }
    __ptr[i] = next_ugly;
    for (j = 0; j < primesSize; j = j + 1) {
      if (__ptr_01[j] == next_ugly) {
        iVar1 = primes[j];
        iVar3 = *(int *)((long)__ptr_00 + (long)j * 4) + 1;
        *(int *)((long)__ptr_00 + (long)j * 4) = iVar3;
        __ptr_01[j] = (long)iVar1 * __ptr[iVar3];
      }
    }
  }
  lVar2 = __ptr[n + -1];
  free(__ptr);
  free(__ptr_00);
  free(__ptr_01);
  return lVar2;
}