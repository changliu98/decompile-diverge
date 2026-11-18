int func0(int x,int y)

{
  int y_local;
  int x_local;
  int local_c;
  
  if (y < x) {
    local_c = -1;
  }
  else if ((y == x) && (y % 2 == 1)) {
    local_c = -1;
  }
  else {
    local_c = y;
    if (y % 2 == 1) {
      local_c = y + -1;
    }
  }
  return local_c;
}