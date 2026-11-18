void func0(int *x,int size,int **out,int *out_size)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  bool bVar4;
  int temp;
  int j;
  int i_1;
  _Bool has_even_digit;
  int num;
  int i;
  int *out_size_local;
  int **out_local;
  int size_local;
  int *x_local;
  
  piVar3 = malloc((long)size << 2);
  *out = piVar3;
  *out_size = 0;
  for (i = 0; i < size; i = i + 1) {
    num = x[i];
    bVar4 = num == 0;
    while( true ) {
      bVar2 = false;
      if (0 < num) {
        bVar2 = (bool)(bVar4 ^ 1);
      }
      if (!bVar2) break;
      if (num % 2 == 0) {
        bVar4 = true;
      }
      num = num / 10;
    }
    if (!bVar4) {
      (*out)[*out_size] = x[i];
      *out_size = *out_size + 1;
    }
  }
  for (i_1 = 0; i_1 < *out_size + -1; i_1 = i_1 + 1) {
    for (j = 0; j < (*out_size - i_1) + -1; j = j + 1) {
      if ((*out)[j + 1] < (*out)[j]) {
        iVar1 = (*out)[j];
        (*out)[j] = (*out)[j + 1];
        (*out)[j + 1] = iVar1;
      }
    }
  }
  return;
}