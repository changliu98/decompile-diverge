void func0(int *l,int size,int *out)

{
  undefined4 uVar1;
  void *__ptr;
  int temp;
  int min_idx;
  int third_size;
  int k;
  int i;
  int *third;
  int *out_local;
  int size_local;
  int *l_local;
  
  __ptr = malloc((long)(size / 3 + 1) << 2);
  third_size = 0;
  for (i = 0; i * 3 < size; i = i + 1) {
    *(int *)((long)__ptr + (long)i * 4) = l[i * 3];
    third_size = third_size + 1;
  }
  for (i = 0; i < third_size + -1; i = i + 1) {
    min_idx = i;
    k = i;
    while (k = k + 1, k < third_size) {
      if (*(int *)((long)__ptr + (long)k * 4) < *(int *)((long)__ptr + (long)min_idx * 4)) {
        min_idx = k;
      }
    }
    if (min_idx != i) {
      uVar1 = *(undefined4 *)((long)__ptr + (long)i * 4);
      *(undefined4 *)((long)__ptr + (long)i * 4) = *(undefined4 *)((long)__ptr + (long)min_idx * 4);
      *(undefined4 *)((long)__ptr + (long)min_idx * 4) = uVar1;
    }
  }
  for (i = 0; i < size; i = i + 1) {
    if (i % 3 == 0) {
      out[i] = *(int *)((long)__ptr + (long)(i / 3) * 4);
    }
    else {
      out[i] = l[i];
    }
  }
  free(__ptr);
  return;
}