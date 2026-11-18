size_t t_add(size_t a,size_t b,int *ok)

{
  size_t local_40;
  ulong local_38;
  bool local_21;
  int *ok_local;
  size_t b_local;
  size_t a_local;
  
  local_21 = false;
  if (*ok != 0) {
    local_38 = b;
    if (b < a) {
      local_38 = a;
    }
    local_21 = local_38 <= a + b;
  }
  *ok = (uint)local_21;
  if (*ok == 0) {
    local_40 = 0;
  }
  else {
    local_40 = a + b;
  }
  return local_40;
}