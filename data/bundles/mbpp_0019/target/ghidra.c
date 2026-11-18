_Bool func0(int *arraynums,int length)

{
  bool bVar1;
  int j;
  int i;
  _Bool found_duplicate;
  int length_local;
  int *arraynums_local;
  
  bVar1 = false;
  i = 0;
  do {
    j = i;
    if (length <= i) {
      return bVar1;
    }
    do {
      j = j + 1;
      if (length <= j) goto LAB_0010122f;
    } while (arraynums[i] != arraynums[j]);
    bVar1 = true;
LAB_0010122f:
    if (bVar1) {
      return true;
    }
    i = i + 1;
  } while( true );
}