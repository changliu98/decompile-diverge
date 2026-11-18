void func0(int *my_list,int n)

{
  void *__ptr;
  int a;
  int j_1;
  int pos;
  int i_1;
  int j;
  int *buckets;
  int i;
  int max_value;
  int n_local;
  int *my_list_local;
  
  max_value = 0;
  for (i = 0; i < n; i = i + 1) {
    if (max_value < my_list[i]) {
      max_value = my_list[i];
    }
  }
  __ptr = malloc((long)(max_value + 1) << 2);
  for (j = 0; j <= max_value; j = j + 1) {
    *(undefined4 *)((long)__ptr + (long)j * 4) = 0;
  }
  for (i_1 = 0; i_1 < n; i_1 = i_1 + 1) {
    *(int *)((long)__ptr + (long)my_list[i_1] * 4) =
         *(int *)((long)__ptr + (long)my_list[i_1] * 4) + 1;
  }
  pos = 0;
  for (j_1 = 0; j_1 <= max_value; j_1 = j_1 + 1) {
    for (a = 0; a < *(int *)((long)__ptr + (long)j_1 * 4); a = a + 1) {
      my_list[pos] = j_1;
      pos = pos + 1;
    }
  }
  free(__ptr);
  return;
}