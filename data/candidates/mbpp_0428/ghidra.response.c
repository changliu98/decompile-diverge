void func0(int *my_list,int length)

{
  int iVar1;
  bool bVar2;
  int j;
  int current_item;
  int i;
  int gap;
  int length_local;
  int *my_list_local;
  
  gap = length;
  while (gap = gap / 2, 0 < gap) {
    for (i = gap; i < length; i = i + 1) {
      iVar1 = my_list[i];
      j = i;
      while( true ) {
        bVar2 = false;
        if (gap <= j) {
          bVar2 = iVar1 < my_list[j - gap];
        }
        if (!bVar2) break;
        my_list[j] = my_list[j - gap];
        j = j - gap;
      }
      my_list[j] = iVar1;
    }
  }
  return;
}