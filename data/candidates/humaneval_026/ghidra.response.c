int * func0(int *numbers,int size,int *new_size)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  void *__ptr;
  void *__ptr_00;
  int j_2;
  int in_has2_1;
  int num_1;
  int i_1;
  int j_1;
  int in_has1;
  int j;
  int in_has2;
  int num;
  int i;
  int out_count;
  int has2_count;
  int has1_count;
  int *has2;
  int *has1;
  int *out;
  int *new_size_local;
  int size_local;
  int *numbers_local;
  
  piVar3 = malloc((long)size << 2);
  __ptr = calloc((long)size,4);
  __ptr_00 = calloc((long)size,4);
  has1_count = 0;
  has2_count = 0;
  out_count = 0;
  i = 0;
  do {
    if (size <= i) {
      i_1 = 0;
      do {
        if (size <= i_1) {
          *new_size = out_count;
          free(__ptr);
          free(__ptr_00);
          return piVar3;
        }
        bVar2 = false;
        for (j_2 = 0; j_2 < has2_count; j_2 = j_2 + 1) {
          if (*(int *)((long)__ptr_00 + (long)j_2 * 4) == numbers[i_1]) {
            bVar2 = true;
            break;
          }
        }
        if (!bVar2) {
          piVar3[out_count] = numbers[i_1];
          out_count = out_count + 1;
        }
        i_1 = i_1 + 1;
      } while( true );
    }
    iVar1 = numbers[i];
    bVar2 = false;
    for (j = 0; j < has2_count; j = j + 1) {
      if (*(int *)((long)__ptr_00 + (long)j * 4) == iVar1) {
        bVar2 = true;
        break;
      }
    }
    if (!bVar2) {
      bVar2 = false;
      for (j_1 = 0; j_1 < has1_count; j_1 = j_1 + 1) {
        if (*(int *)((long)__ptr + (long)j_1 * 4) == iVar1) {
          bVar2 = true;
          break;
        }
      }
      if (bVar2) {
        *(int *)((long)__ptr_00 + (long)has2_count * 4) = iVar1;
        has2_count = has2_count + 1;
      }
      else {
        *(int *)((long)__ptr + (long)has1_count * 4) = iVar1;
        has1_count = has1_count + 1;
      }
    }
    i = i + 1;
  } while( true );
}