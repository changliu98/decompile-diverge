int func0(int *price,int n,int k)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  int aiStack_68 [9];
  int curr_price;
  int x;
  int max_so_far;
  int j;
  int i;
  unsigned_long __vla_expr1;
  unsigned_long __vla_expr0;
  int k_local;
  int n_local;
  int *price_local;
  
                    /* Unresolved local var: int[212][221] final_profit@[???] */
  uVar3 = (ulong)(uint)n;
  lVar1 = -0x68 - ((k + 1) * uVar3 * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i <= k; i = i + 1) {
    for (j = 0; j < n; j = j + 1) {
      if ((i == 0) || (j == 0)) {
        *(undefined4 *)((long)aiStack_68 + (long)j * 4 + (long)i * uVar3 * 4 + lVar1 + 0x68) = 0;
      }
      else {
        max_so_far = 0;
        for (x = 0; x < j; x = x + 1) {
          iVar2 = (price[j] - price[x]) +
                  *(int *)((long)aiStack_68 +
                          (long)x * 4 + (long)(i + -1) * uVar3 * 4 + lVar1 + 0x68);
          if (max_so_far < iVar2) {
            max_so_far = iVar2;
          }
        }
        if (max_so_far <
            *(int *)((long)aiStack_68 + (long)(j + -1) * 4 + (long)i * uVar3 * 4 + lVar1 + 0x68)) {
          aiStack_68[3] =
               *(int *)((long)aiStack_68 + (long)(j + -1) * 4 + (long)i * uVar3 * 4 + lVar1 + 0x68);
        }
        else {
          aiStack_68[3] = max_so_far;
        }
        *(int *)((long)aiStack_68 + (long)j * 4 + (long)i * uVar3 * 4 + lVar1 + 0x68) =
             aiStack_68[3];
      }
    }
  }
  return *(int *)((long)aiStack_68 + (long)(n + -1) * 4 + (long)k * uVar3 * 4 + lVar1 + 0x68);
}