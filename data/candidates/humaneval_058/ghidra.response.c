int * func0(int *l1,int size1,int *l2,int size2,int *out_size)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  int temp;
  int exists_in_out;
  int m;
  int j;
  int i;
  int k;
  int *out;
  int *out_size_local;
  int size2_local;
  int *l2_local;
  int size1_local;
  int *l1_local;
  
  piVar3 = malloc((long)size1 << 2);
  k = 0;
  i = 0;
  do {
    if (size1 <= i) {
      for (i = 0; i < k + -1; i = i + 1) {
        for (j = 0; j < (k - i) + -1; j = j + 1) {
          if (piVar3[j + 1] < piVar3[j]) {
            iVar1 = piVar3[j];
            piVar3[j] = piVar3[j + 1];
            piVar3[j + 1] = iVar1;
          }
        }
      }
      *out_size = k;
      return piVar3;
    }
    bVar2 = false;
    for (m = 0; m < k; m = m + 1) {
      if (piVar3[m] == l1[i]) {
        bVar2 = true;
        break;
      }
    }
    if (!bVar2) {
      for (j = 0; j < size2; j = j + 1) {
        if (l1[i] == l2[j]) {
          piVar3[k] = l1[i];
          k = k + 1;
          break;
        }
      }
    }
    i = i + 1;
  } while( true );
}