int sortedarray_index_of(SortedArray *sortedarray,SortedArrayValue data)

{
  uint uVar1;
  int iVar2;
  uint local_34;
  int order;
  uint index;
  uint right;
  uint left;
  SortedArrayValue data_local;
  SortedArray *sortedarray_local;
  
  if (sortedarray != (SortedArray *)0x0) {
    left = 0;
    local_34 = sortedarray->length;
    if (local_34 < 2) {
      local_34 = 0;
    }
    right = local_34;
    uVar1 = right;
    while (right = uVar1, left != right) {
      uVar1 = left + right >> 1;
      iVar2 = (*sortedarray->cmp_func)(data,sortedarray->data[uVar1]);
      if (-1 < iVar2) {
        if (iVar2 < 1) {
          return uVar1;
        }
        left = uVar1 + 1;
        uVar1 = right;
      }
    }
  }
  return -1;
}