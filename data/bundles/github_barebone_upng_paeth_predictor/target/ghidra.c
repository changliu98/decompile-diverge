int paeth_predictor(int a,int b,int c)

{
  int local_34;
  int local_30;
  int local_2c;
  int pc;
  int pb;
  int pa;
  int p;
  int c_local;
  int b_local;
  int a_local;
  int local_c;
  
  local_34 = (a + b) - c;
  if (a < local_34) {
    local_2c = local_34 - a;
  }
  else {
    local_2c = a - local_34;
  }
  if (b < local_34) {
    local_30 = local_34 - b;
  }
  else {
    local_30 = b - local_34;
  }
  if (c < local_34) {
    local_34 = local_34 - c;
  }
  else {
    local_34 = c - local_34;
  }
  if (((local_30 < local_2c) || (local_c = a, local_34 < local_2c)) &&
     (local_c = c, local_30 <= local_34)) {
    local_c = b;
  }
  return local_c;
}