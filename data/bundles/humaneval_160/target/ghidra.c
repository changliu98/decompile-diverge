int func0(char **operato,int *operand,int operato_size,int operand_size)

{
  int iVar1;
  int *__ptr;
  void *__ptr_00;
  double dVar2;
  int result;
  int i_3;
  int i_2;
  int i_1;
  int i;
  int *posto;
  int *num;
  int operand_size_local;
  int operato_size_local;
  int *operand_local;
  char **operato_local;
  
  __ptr = malloc((long)operand_size << 2);
  __ptr_00 = malloc((long)operand_size << 2);
  for (i = 0; i < operand_size; i = i + 1) {
    __ptr[i] = operand[i];
    *(int *)((long)__ptr_00 + (long)i * 4) = i;
  }
  for (i_1 = 0; i_1 < operato_size; i_1 = i_1 + 1) {
    iVar1 = strcmp(operato[i_1],"**");
    if (iVar1 == 0) {
      while (*(int *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)i_1 * 4) * 4) !=
             *(int *)((long)__ptr_00 + (long)i_1 * 4)) {
        *(undefined4 *)((long)__ptr_00 + (long)i_1 * 4) =
             *(undefined4 *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)i_1 * 4) * 4);
      }
      while (*(int *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)(i_1 + 1) * 4) * 4) !=
             *(int *)((long)__ptr_00 + (long)(i_1 + 1) * 4)) {
        *(undefined4 *)((long)__ptr_00 + (long)(i_1 + 1) * 4) =
             *(undefined4 *)
              ((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)(i_1 + 1) * 4) * 4);
      }
      dVar2 = pow((double)__ptr[*(int *)((long)__ptr_00 + (long)i_1 * 4)],
                  (double)__ptr[*(int *)((long)__ptr_00 + (long)(i_1 + 1) * 4)]);
      __ptr[*(int *)((long)__ptr_00 + (long)i_1 * 4)] = (int)dVar2;
      *(undefined4 *)((long)__ptr_00 + (long)(i_1 + 1) * 4) =
           *(undefined4 *)((long)__ptr_00 + (long)i_1 * 4);
    }
  }
  for (i_2 = 0; i_2 < operato_size; i_2 = i_2 + 1) {
    iVar1 = strcmp(operato[i_2],"*");
    if ((iVar1 == 0) || (iVar1 = strcmp(operato[i_2],"//"), iVar1 == 0)) {
      while (*(int *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)i_2 * 4) * 4) !=
             *(int *)((long)__ptr_00 + (long)i_2 * 4)) {
        *(undefined4 *)((long)__ptr_00 + (long)i_2 * 4) =
             *(undefined4 *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)i_2 * 4) * 4);
      }
      while (*(int *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)(i_2 + 1) * 4) * 4) !=
             *(int *)((long)__ptr_00 + (long)(i_2 + 1) * 4)) {
        *(undefined4 *)((long)__ptr_00 + (long)(i_2 + 1) * 4) =
             *(undefined4 *)
              ((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)(i_2 + 1) * 4) * 4);
      }
      iVar1 = strcmp(operato[i_2],"*");
      if (iVar1 == 0) {
        iVar1 = *(int *)((long)__ptr_00 + (long)i_2 * 4);
        __ptr[iVar1] = __ptr[*(int *)((long)__ptr_00 + (long)(i_2 + 1) * 4)] * __ptr[iVar1];
      }
      else {
        iVar1 = *(int *)((long)__ptr_00 + (long)i_2 * 4);
        __ptr[iVar1] = __ptr[iVar1] / __ptr[*(int *)((long)__ptr_00 + (long)(i_2 + 1) * 4)];
      }
      *(undefined4 *)((long)__ptr_00 + (long)(i_2 + 1) * 4) =
           *(undefined4 *)((long)__ptr_00 + (long)i_2 * 4);
    }
  }
  for (i_3 = 0; i_3 < operato_size; i_3 = i_3 + 1) {
    iVar1 = strcmp(operato[i_3],"+");
    if ((iVar1 == 0) || (iVar1 = strcmp(operato[i_3],"-"), iVar1 == 0)) {
      while (*(int *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)i_3 * 4) * 4) !=
             *(int *)((long)__ptr_00 + (long)i_3 * 4)) {
        *(undefined4 *)((long)__ptr_00 + (long)i_3 * 4) =
             *(undefined4 *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)i_3 * 4) * 4);
      }
      while (*(int *)((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)(i_3 + 1) * 4) * 4) !=
             *(int *)((long)__ptr_00 + (long)(i_3 + 1) * 4)) {
        *(undefined4 *)((long)__ptr_00 + (long)(i_3 + 1) * 4) =
             *(undefined4 *)
              ((long)__ptr_00 + (long)*(int *)((long)__ptr_00 + (long)(i_3 + 1) * 4) * 4);
      }
      iVar1 = strcmp(operato[i_3],"+");
      if (iVar1 == 0) {
        iVar1 = *(int *)((long)__ptr_00 + (long)i_3 * 4);
        __ptr[iVar1] = __ptr[*(int *)((long)__ptr_00 + (long)(i_3 + 1) * 4)] + __ptr[iVar1];
      }
      else {
        iVar1 = *(int *)((long)__ptr_00 + (long)i_3 * 4);
        __ptr[iVar1] = __ptr[iVar1] - __ptr[*(int *)((long)__ptr_00 + (long)(i_3 + 1) * 4)];
      }
      *(undefined4 *)((long)__ptr_00 + (long)(i_3 + 1) * 4) =
           *(undefined4 *)((long)__ptr_00 + (long)i_3 * 4);
    }
  }
  iVar1 = *__ptr;
  free(__ptr);
  free(__ptr_00);
  return iVar1;
}