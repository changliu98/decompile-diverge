int * func0(int n,int *count)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  int k;
  int isp;
  int j;
  int i;
  int *out;
  int *count_local;
  int n_local;
  
  piVar3 = malloc((long)n << 2);
  *count = 0;
  i = 2;
  do {
    if (n <= i) {
      return piVar3;
    }
    bVar2 = true;
    j = 0;
    while( true ) {
      if ((*count <= j) || (iVar1 = piVar3[j], i < iVar1 * iVar1)) goto LAB_0010127c;
      if (i % iVar1 == 0) break;
      j = j + 1;
    }
    bVar2 = false;
LAB_0010127c:
    if (bVar2) {
      piVar3[*count] = i;
      *count = *count + 1;
    }
    i = i + 1;
  } while( true );
}