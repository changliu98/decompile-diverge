int func0(char *str)

{
  long lVar1;
  int iVar2;
  size_t sVar3;
  ulong uVar4;
  int aiStack_58 [6];
  int j_1;
  int i_1;
  int j;
  int i;
  unsigned_long __vla_expr1;
  unsigned_long __vla_expr0;
  int n;
  char *str_local;
  
  str_local = str;
                    /* Unresolved local var: int[196][205] dp@[???] */
  sVar3 = strlen(str);
  iVar2 = (int)sVar3;
  uVar4 = (ulong)(iVar2 + 1);
  lVar1 = -0x58 - (uVar4 * uVar4 * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i <= iVar2; i = i + 1) {
    for (j = 0; j <= iVar2; j = j + 1) {
      *(undefined4 *)((long)aiStack_58 + (long)j * 4 + (long)i * uVar4 * 4 + lVar1 + 0x58) = 0;
    }
  }
  for (i_1 = 1; i_1 <= iVar2; i_1 = i_1 + 1) {
    for (j_1 = 1; j_1 <= iVar2; j_1 = j_1 + 1) {
      if ((str_local[i_1 + -1] == str_local[j_1 + -1]) && (i_1 != j_1)) {
        *(int *)((long)aiStack_58 + (long)j_1 * 4 + (long)i_1 * uVar4 * 4 + lVar1 + 0x58) =
             *(int *)((long)aiStack_58 +
                     (long)(j_1 + -1) * 4 + (long)(i_1 + -1) * uVar4 * 4 + lVar1 + 0x58) + 1;
      }
      else {
        if (*(int *)((long)aiStack_58 + (long)j_1 * 4 + (long)(i_1 + -1) * uVar4 * 4 + lVar1 + 0x58)
            < *(int *)((long)aiStack_58 +
                      (long)(j_1 + -1) * 4 + (long)i_1 * uVar4 * 4 + lVar1 + 0x58)) {
          aiStack_58[1] =
               *(undefined4 *)
                ((long)aiStack_58 + (long)(j_1 + -1) * 4 + (long)i_1 * uVar4 * 4 + lVar1 + 0x58);
        }
        else {
          aiStack_58[1] =
               *(undefined4 *)
                ((long)aiStack_58 + (long)j_1 * 4 + (long)(i_1 + -1) * uVar4 * 4 + lVar1 + 0x58);
        }
        *(int *)((long)aiStack_58 + (long)j_1 * 4 + (long)i_1 * uVar4 * 4 + lVar1 + 0x58) =
             aiStack_58[1];
      }
    }
  }
  return *(int *)((long)aiStack_58 + (long)iVar2 * 4 + (long)iVar2 * uVar4 * 4 + lVar1 + 0x58);
}