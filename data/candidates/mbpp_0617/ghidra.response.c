int func0(int a,int b,int d)

{
  int local_24;
  int local_20;
  int temp;
  int d_local;
  int b_local;
  int a_local;
  int local_c;
  
  local_20 = b;
  if (a < b) {
    local_20 = a;
  }
  local_24 = b;
  if (b < a) {
    local_24 = a;
  }
  if (d < local_24) {
    if (d == 0) {
      local_c = 0;
    }
    else if (d == local_20) {
      local_c = 1;
    }
    else {
      local_c = 2;
    }
  }
  else {
    local_c = (d + local_24 + -1) / local_24;
  }
  return local_c;
}