size_t spc_used(size_t head,size_t tail,size_t size)

{
  int iVar1;
  int diff;
  size_t size_local;
  size_t tail_local;
  size_t head_local;
  undefined8 local_10;
  
  iVar1 = (int)head - (int)tail;
  if (iVar1 < 0) {
    local_10 = size + (long)iVar1;
  }
  else {
    local_10 = (size_t)iVar1;
  }
  return local_10;
}