int dupfd(int from,int *to)

{
  int iVar1;
  int *to_local;
  int from_local;
  undefined4 local_c;
  
  if (from == -1) {
    *to = -1;
    local_c = 1;
  }
  else {
    iVar1 = dup(from);
    *to = iVar1;
    local_c = (uint)(*to != -1);
  }
  return local_c;
}