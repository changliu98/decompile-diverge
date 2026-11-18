int func0(char *str)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  size_t sVar5;
  ulong uVar6;
  int aiStack_58 [6];
  int j;
  int i_1;
  int cl;
  int i;
  unsigned_long __vla_expr1;
  unsigned_long __vla_expr0;
  int n;
  char *str_local;
  
  str_local = str;
                    /* Unresolved local var: int[196][205] L@[???] */
  sVar5 = strlen(str);
  iVar2 = (int)sVar5;
  uVar6 = sVar5 & 0xffffffff;
  lVar1 = -0x58 - (uVar6 * uVar6 * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i < iVar2; i = i + 1) {
    *(undefined4 *)((long)aiStack_58 + (long)i * 4 + (long)i * uVar6 * 4 + lVar1 + 0x58) = 1;
  }
  for (cl = 2; cl <= iVar2; cl = cl + 1) {
    for (i_1 = 0; i_1 < (iVar2 - cl) + 1; i_1 = i_1 + 1) {
      iVar3 = i_1 + cl;
      iVar4 = iVar3 + -1;
      if ((str_local[i_1] == str_local[iVar4]) && (cl == 2)) {
        *(undefined4 *)((long)aiStack_58 + (long)iVar4 * 4 + (long)i_1 * uVar6 * 4 + lVar1 + 0x58) =
             2;
      }
      else if (str_local[i_1] == str_local[iVar4]) {
        *(int *)((long)aiStack_58 + (long)iVar4 * 4 + (long)i_1 * uVar6 * 4 + lVar1 + 0x58) =
             *(int *)((long)aiStack_58 +
                     (long)(iVar3 + -2) * 4 + (long)(i_1 + 1) * uVar6 * 4 + lVar1 + 0x58) + 2;
      }
      else {
        if (*(int *)((long)aiStack_58 + (long)iVar4 * 4 + (long)(i_1 + 1) * uVar6 * 4 + lVar1 + 0x58
                    ) <
            *(int *)((long)aiStack_58 +
                    (long)(iVar3 + -2) * 4 + (long)i_1 * uVar6 * 4 + lVar1 + 0x58)) {
          aiStack_58[1] =
               *(undefined4 *)
                ((long)aiStack_58 + (long)(iVar3 + -2) * 4 + (long)i_1 * uVar6 * 4 + lVar1 + 0x58);
        }
        else {
          aiStack_58[1] =
               *(undefined4 *)
                ((long)aiStack_58 + (long)iVar4 * 4 + (long)(i_1 + 1) * uVar6 * 4 + lVar1 + 0x58);
        }
        *(int *)((long)aiStack_58 + (long)iVar4 * 4 + (long)i_1 * uVar6 * 4 + lVar1 + 0x58) =
             aiStack_58[1];
      }
    }
  }
  return *(int *)((long)aiStack_58 + (long)(iVar2 + -1) * 4 + lVar1 + 0x58);
}