_Bool func0(int *dlist,int size,int item,int *pos)

{
  _Bool _Var1;
  byte bVar2;
  _Bool found;
  int *pos_local;
  int item_local;
  int size_local;
  int *dlist_local;
  
  *pos = 0;
  _Var1 = false;
  while( true ) {
    bVar2 = 0;
    if (*pos < size) {
      bVar2 = _Var1 ^ 1;
    }
    if (bVar2 == 0) break;
    if (dlist[*pos] == item) {
      _Var1 = true;
    }
    else {
      *pos = *pos + 1;
    }
  }
  return _Var1;
}