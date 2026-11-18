void func0(int *array,int size,int **out_array,int *out_size)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int temp_1;
  int temp;
  int j;
  int i_1;
  int shouldSortAscending;
  int i;
  int *out_size_local;
  int **out_array_local;
  int size_local;
  int *array_local;
  
  *out_size = size;
  if (size == 0) {
    *out_array = (int *)0x0;
  }
  else {
    piVar4 = malloc((long)size << 2);
    *out_array = piVar4;
    if (*out_array == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    for (i = 0; i < size; i = i + 1) {
      (*out_array)[i] = array[i];
    }
    iVar1 = *array;
    iVar2 = array[size + -1];
    for (i_1 = 0; j = i_1, i_1 < size + -1; i_1 = i_1 + 1) {
      while (j = j + 1, j < size) {
        if ((iVar1 + iVar2) % 2 == 1) {
          if ((*out_array)[j] < (*out_array)[i_1]) {
            iVar3 = (*out_array)[i_1];
            (*out_array)[i_1] = (*out_array)[j];
            (*out_array)[j] = iVar3;
          }
        }
        else if ((*out_array)[i_1] < (*out_array)[j]) {
          iVar3 = (*out_array)[i_1];
          (*out_array)[i_1] = (*out_array)[j];
          (*out_array)[j] = iVar3;
        }
      }
    }
  }
  return;
}