int summe(int *n,int *s)

{
  int iVar1;
  undefined1 local_19;
  int *s_local;
  int *n_local;
  
  local_19 = true;
  if (*n != 0) {
    *s = *n + *s;
    *n = *n + -1;
    iVar1 = summe(n,s);
    local_19 = iVar1 != 0;
  }
  return (int)local_19;
}