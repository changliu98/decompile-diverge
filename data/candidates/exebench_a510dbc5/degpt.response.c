void chartobit(int val,char *v)

{
  char cVar1;
  int i;
  char *v_local;
  int val_local;
  
  val_local = val;
  for (i = 7; 0 < i; i = i + -1) {
    cVar1 = '0';
    if (val_local % 2 == 1) {
      cVar1 = '1';
    }
    v[i] = cVar1;
    val_local = val_local / 2;
  }
  cVar1 = '0';
  if (val_local % 2 == 1) {
    cVar1 = '1';
  }
  *v = cVar1;
  return;
}