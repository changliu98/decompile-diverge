int * func0(int *l,int size,int *out_size)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  int temp;
  int j;
  int i;
  int out_count;
  int found;
  int *out;
  int *out_size_local;
  int size_local;
  int *l_local;
  
  piVar3 = malloc((long)size << 2);
  out_count = 0;
  i = 0;
  do {
    if (size <= i) {
      for (i = 0; j = i, i < out_count + -1; i = i + 1) {
        while (j = j + 1, j < out_count) {
          if (piVar3[j] < piVar3[i]) {
            iVar1 = piVar3[i];
            piVar3[i] = piVar3[j];
            piVar3[j] = iVar1;
          }
        }
      }
      *out_size = out_count;
      return piVar3;
    }
    bVar2 = false;
    for (j = 0; j < out_count; j = j + 1) {
      if (l[i] == piVar3[j]) {
        bVar2 = true;
        break;
      }
    }
    if (!bVar2) {
      piVar3[out_count] = l[i];
      out_count = out_count + 1;
    }
    i = i + 1;
  } while( true );
}