int func0(int x,int y)

{
  int y_local;
  int x_local;
  undefined4 local_c;
  
  if (y < 0) {
    local_c = func0(x,-y);
    local_c = -local_c;
  }
  else if (y == 0) {
    local_c = 0;
  }
  else {
    local_c = x;
    if (y != 1) {
      local_c = func0(x,y + -1);
      local_c = x + local_c;
    }
  }
  return local_c;
}