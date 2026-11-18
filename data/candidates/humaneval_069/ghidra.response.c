int func0(int *lst,int size)

{
  void *__ptr;
  int i;
  int max;
  int *freq;
  int size_local;
  int *lst_local;
  
  __ptr = calloc((long)(size + 1),4);
  max = -1;
  for (i = 0; i < size; i = i + 1) {
    *(int *)((long)__ptr + (long)lst[i] * 4) = *(int *)((long)__ptr + (long)lst[i] * 4) + 1;
    if ((lst[i] <= *(int *)((long)__ptr + (long)lst[i] * 4)) && (max < lst[i])) {
      max = lst[i];
    }
  }
  free(__ptr);
  return max;
}