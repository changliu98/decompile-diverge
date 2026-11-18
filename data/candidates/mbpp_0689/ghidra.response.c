int func0(int *arr,int n)

{
  int aiStack_58 [4];
  undefined4 *local_48;
  int j;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *arr_local;
  int local_c;
  
                    /* Unresolved local var: int[201] jumps@[???] */
  local_48 = (undefined4 *)((long)aiStack_58 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0));
  if ((n == 0) || (*arr == 0)) {
    local_c = 0x7fffffff;
  }
  else {
    n_local = n;
    arr_local = arr;
    *local_48 = 0;
    for (i = 1; i < n_local; i = i + 1) {
      local_48[i] = 0x7fffffff;
      for (j = 0; j < i; j = j + 1) {
        if ((i <= j + arr_local[j]) && (local_48[j] != 0x7fffffff)) {
          if ((int)local_48[i] < local_48[j] + 1) {
            aiStack_58[3] = local_48[i];
          }
          else {
            aiStack_58[3] = local_48[j] + 1;
          }
          local_48[i] = aiStack_58[3];
          break;
        }
      }
    }
    local_c = local_48[n_local + -1];
  }
  return local_c;
}