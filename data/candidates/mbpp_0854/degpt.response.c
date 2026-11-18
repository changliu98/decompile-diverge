void func0(int *rawheap,int size)

{
  int iVar1;
  int temp;
  int j;
  int i;
  int size_local;
  int *rawheap_local;
  
  i = size / 2;
  do {
    i = i + -1;
    j = i;
    if (i < 0) {
      return;
    }
    while( true ) {
      iVar1 = j * 2;
      j = iVar1 + 1;
      if (size <= j) break;
      if ((iVar1 + 2 < size) && (rawheap[iVar1 + 2] < rawheap[j])) {
        j = iVar1 + 2;
      }
      if (rawheap[i] <= rawheap[j]) break;
      iVar1 = rawheap[i];
      rawheap[i] = rawheap[j];
      rawheap[j] = iVar1;
      i = j + -1;
    }
  } while( true );
}