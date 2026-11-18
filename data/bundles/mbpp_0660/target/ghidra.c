int func0(int l1,int r1,int l2,int r2,int *x,int *y)

{
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int *y_local;
  int *x_local;
  int r2_local;
  int l2_local;
  int r1_local;
  int l1_local;
  
  if (l1 == l2) {
    local_30 = -1;
  }
  else {
    local_2c = l2;
    if (l1 < l2) {
      local_2c = l1;
    }
    local_30 = local_2c;
  }
  *x = local_30;
  if (r1 == r2) {
    local_38 = -1;
  }
  else {
    local_34 = r2;
    if (r2 < r1) {
      local_34 = r1;
    }
    local_38 = local_34;
  }
  *y = local_38;
  return 0;
}