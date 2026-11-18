int func0(int a,int b)

{
  int local_24;
  int local_20;
  int high;
  int low;
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
  if (local_20 == 0) {
    local_c = local_24;
  }
  else if (local_20 == 1) {
    local_c = 1;
  }
  else {
    local_c = func0(local_20,local_24 % local_20);
  }
  return local_c;
}