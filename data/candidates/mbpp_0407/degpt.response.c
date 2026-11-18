int func0(int n)

{
  int iVar1;
  size_t sVar2;
  size_t k;
  size_t j_1;
  size_t j;
  char y;
  size_t z_len;
  char cStack_38;
  char z [11];
  int i;
  size_t length;
  char nums [11];
  int n_local;
  
  sprintf(nums,"%d",(ulong)(uint)n);
  sVar2 = strlen(nums);
  i = (int)sVar2 + -2;
  while( true ) {
    if (i < 0) {
      return 0;
    }
    if (nums[i] < nums[i + 1]) break;
    i = i + -1;
  }
  strcpy(z,nums + i);
  sVar2 = strlen(z);
  y = z[1];
  for (j = 1; j < sVar2; j = j + 1) {
    if ((z[0] < z[j]) && (z[j] < y)) {
      y = z[j];
    }
  }
  j_1 = 0;
  while( true ) {
    if (sVar2 <= j_1) goto LAB_0010138a;
    if (z[j_1] == y) break;
    j_1 = j_1 + 1;
  }
  for (k = j_1; k < sVar2 - 1; k = k + 1) {
    z[k] = z[k + 1];
  }
  z[sVar2 - 1] = '\0';
LAB_0010138a:
  sVar2 = strlen(z);
  qsort(z,sVar2,1,(__compar_fn_t)PTR_strcmp_00103fd8);
  nums[i] = y;
  strcpy(nums + (long)i + 1,z);
  iVar1 = atoi(nums);
  return iVar1;
}