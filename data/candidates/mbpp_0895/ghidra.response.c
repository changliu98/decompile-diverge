int func0(int *A,int n)

{
  int iVar1;
  int aiStack_58 [4];
  int *local_48;
  int option3;
  int option2;
  int option1;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *A_local;
  int local_c;
  
                    /* Unresolved local var: int[201] look_up@[???] */
  if (n == 1) {
    local_c = *A;
  }
  else {
    local_48 = (int *)((long)aiStack_58 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0));
    n_local = n;
    A_local = A;
    *local_48 = *A;
    if (A_local[1] < *A_local) {
      aiStack_58[3] = *A_local;
    }
    else {
      aiStack_58[3] = A_local[1];
    }
    local_48[1] = aiStack_58[3];
    for (i = 2; i < n_local; i = i + 1) {
      aiStack_58[2] = local_48[i + -2] + A_local[i];
      iVar1 = A_local[i];
      if (aiStack_58[2] < local_48[i + -1]) {
        aiStack_58[2] = local_48[i + -1];
      }
      local_48[i] = aiStack_58[2];
      aiStack_58[1] = iVar1;
      if (iVar1 < local_48[i]) {
        aiStack_58[1] = local_48[i];
      }
      local_48[i] = aiStack_58[1];
    }
    local_c = local_48[n_local + -1];
  }
  return local_c;
}