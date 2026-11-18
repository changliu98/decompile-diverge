int sortedarray_insert(SortedArray *sortedarray,SortedArrayValue data)

{
  int iVar1;
  uint uVar2;
  SortedArrayValue *ppvVar3;
  uint local_44;
  SortedArrayValue *data_1;
  uint newsize;
  int order;
  uint index;
  uint right;
  uint left;
  SortedArrayValue data_local;
  SortedArray *sortedarray_local;
  int local_c;
  
  if (sortedarray == (SortedArray *)0x0) {
    local_c = 0;
  }
  else {
    left = 0;
    local_44 = sortedarray->length;
    index = 0;
    if (local_44 < 2) {
      local_44 = 0;
    }
    right = local_44;
    uVar2 = right;
    while (right = uVar2, left != right) {
      index = left + right >> 1;
      iVar1 = (*sortedarray->cmp_func)(data,sortedarray->data[index]);
      uVar2 = index;
      if (-1 < iVar1) {
        if (iVar1 < 1) break;
        left = index + 1;
        uVar2 = right;
      }
    }
    if ((sortedarray->length != 0) &&
       (iVar1 = (*sortedarray->cmp_func)(data,sortedarray->data[index]), 0 < iVar1)) {
      index = index + 1;
    }
    if (sortedarray->_alloced < sortedarray->length + 1) {
      uVar2 = sortedarray->_alloced << 1;
      ppvVar3 = realloc(sortedarray->data,(ulong)uVar2 << 3);
      if (ppvVar3 == (SortedArrayValue *)0x0) {
        return 0;
      }
      sortedarray->data = ppvVar3;
      sortedarray->_alloced = uVar2;
    }
    memmove(sortedarray->data + (index + 1),sortedarray->data + index,
            (ulong)(sortedarray->length - index) << 3);
    sortedarray->data[index] = data;
    sortedarray->length = sortedarray->length + 1;
    local_c = 1;
  }
  return local_c;
}