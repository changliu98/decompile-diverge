int func0(int *arr,int n)

{
  int iVar1;
  int local_58 [4];
  int local_48;
  int local_44;
  int *local_40;
  int max3;
  int max2;
  int max1;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[201] sum@[???] */
  local_40 = (int *)((long)local_58 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0));
  n_local = n;
  arr_local = arr;
  if (0 < n) {
    *local_40 = *arr;
  }
  if (1 < n_local) {
    local_40[1] = *arr_local + arr_local[1];
  }
  if (2 < n_local) {
    if (arr_local[1] + arr_local[2] < local_40[1]) {
      local_44 = local_40[1];
    }
    else {
      local_44 = arr_local[1] + arr_local[2];
    }
    if (*arr_local + arr_local[2] < local_44) {
      if (arr_local[1] + arr_local[2] < local_40[1]) {
        local_48 = local_40[1];
      }
      else {
        local_48 = arr_local[1] + arr_local[2];
      }
      local_58[3] = local_48;
    }
    else {
      local_58[3] = *arr_local + arr_local[2];
    }
    local_40[2] = local_58[3];
  }
  for (i = 3; i < n_local; i = i + 1) {
    iVar1 = local_40[i + -1];
    local_58[1] = local_40[i + -2] + arr_local[i];
    local_58[0] = arr_local[i] + arr_local[i + -1] + local_40[i + -3];
    local_58[2] = local_58[1];
    if (local_58[1] < iVar1) {
      local_58[2] = iVar1;
    }
    if (local_58[0] < local_58[2]) {
      if (local_58[1] < iVar1) {
        local_58[1] = iVar1;
      }
      local_58[0] = local_58[1];
    }
    local_40[i] = local_58[0];
  }
  return local_40[n_local + -1];
}