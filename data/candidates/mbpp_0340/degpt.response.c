int func0(int *lst,int size)

{
  long lVar1;
  void *__base;
  size_t __nmemb;
  undefined8 uStack_50;
  int aiStack_48 [2];
  void *local_40;
  int i_1;
  int sum;
  int i;
  int count;
  unsigned_long __vla_expr0;
  undefined1 *local_20;
  int size_local;
  int *lst_local;
  
                    /* Unresolved local var: int[239] positive_numbers@[???] */
  local_20 = (undefined1 *)aiStack_48;
  __vla_expr0 = (unsigned_long)(uint)size;
  lVar1 = -(__vla_expr0 * 4 + 0xf & 0xfffffffffffffff0);
  __base = (void *)((long)aiStack_48 + lVar1);
  count = 0;
  for (i = 0; i < size; i = i + 1) {
    if (0 < lst[i]) {
      *(int *)((long)__base + (long)count * 4) = lst[i];
      count = count + 1;
    }
  }
  __nmemb = (size_t)count;
  local_40 = __base;
  size_local = size;
  lst_local = lst;
  *(undefined8 *)((long)&uStack_50 + lVar1) = 0x10129e;
  qsort(__base,__nmemb,4,compare);
  sum = 0;
  for (i_1 = 0; i_1 < 3 && i_1 < count; i_1 = i_1 + 1) {
    sum = *(int *)((long)local_40 + (long)i_1 * 4) + sum;
  }
  return sum;
}