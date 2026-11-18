_Bool func0(int *l,int size)

{
  undefined4 uVar1;
  void *__ptr;
  int i_2;
  _Bool result;
  int temp;
  int j;
  int i_1;
  int i;
  int *sorted;
  int size_local;
  int *l_local;
  
  __ptr = malloc((long)size << 2);
  for (i = 0; i < size; i = i + 1) {
    *(int *)((long)__ptr + (long)i * 4) = l[i];
  }
  for (i_1 = 0; j = i_1, i_1 < size; i_1 = i_1 + 1) {
    while (j = j + 1, j < size) {
      if (*(int *)((long)__ptr + (long)j * 4) < *(int *)((long)__ptr + (long)i_1 * 4)) {
        uVar1 = *(undefined4 *)((long)__ptr + (long)i_1 * 4);
        *(undefined4 *)((long)__ptr + (long)i_1 * 4) = *(undefined4 *)((long)__ptr + (long)j * 4);
        *(undefined4 *)((long)__ptr + (long)j * 4) = uVar1;
      }
    }
  }
  result = true;
  i_2 = 1;
  do {
    if (size <= i_2) {
LAB_0010131c:
      free(__ptr);
      return result;
    }
    if (*(int *)((long)__ptr + (long)i_2 * 4) != *(int *)((long)__ptr + (long)(i_2 + -1) * 4) + 1) {
      result = false;
      goto LAB_0010131c;
    }
    i_2 = i_2 + 1;
  } while( true );
}