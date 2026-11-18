int func0(int *item_list,int size,int item)

{
  int iVar1;
  int mid;
  int found;
  int last;
  int first;
  int item_local;
  int size_local;
  int *item_list_local;
  
  first = 0;
  last = size + -1;
  found = 0;
  while (first <= last && found == 0) {
    iVar1 = (first + last) / 2;
    if (item_list[iVar1] == item) {
      found = 1;
    }
    else if (item < item_list[iVar1]) {
      last = iVar1 + -1;
    }
    else {
      first = iVar1 + 1;
    }
  }
  return found;
}