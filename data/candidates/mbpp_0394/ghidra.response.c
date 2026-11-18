_Bool func0(int *test_tup,int size)

{
  bool bVar1;
  long lVar2;
  int local_48 [3];
  int j;
  _Bool found;
  int ele;
  int i;
  int temp_size;
  unsigned_long __vla_expr0;
  _Bool res;
  int size_local;
  int *test_tup_local;
  
                    /* Unresolved local var: int[212] temp@[???] */
  lVar2 = -0x48 - ((ulong)(uint)size * 4 + 0xf & 0xfffffffffffffff0);
  temp_size = 0;
  i = 0;
  do {
    if (size <= i) {
      return true;
    }
    bVar1 = false;
    for (j = 0; j < temp_size; j = j + 1) {
      if (*(int *)((long)local_48 + (long)j * 4 + lVar2 + 0x48) == test_tup[i]) {
        bVar1 = true;
        break;
      }
    }
    if (bVar1) {
      return false;
    }
    *(int *)((long)local_48 + (long)temp_size * 4 + lVar2 + 0x48) = test_tup[i];
    i = i + 1;
    temp_size = temp_size + 1;
  } while( true );
}