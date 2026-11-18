/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void func0(int *nums,int size)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  float fVar4;
  int temp;
  int i;
  int swapped;
  int gaps;
  float shrink_fact;
  int size_local;
  int *nums_local;
  
  fVar4 = _DAT_00102004;
  bVar3 = true;
  gaps = size;
  while( true ) {
    bVar2 = true;
    if (gaps < 2) {
      bVar2 = bVar3;
    }
    if (!bVar2) break;
    gaps = (int)((float)gaps / fVar4);
    bVar3 = false;
    for (i = 0; gaps + i < size; i = i + 1) {
      if (nums[i + gaps] < nums[i]) {
        iVar1 = nums[i];
        nums[i] = nums[i + gaps];
        nums[i + gaps] = iVar1;
        bVar3 = true;
      }
    }
  }
  return;
}