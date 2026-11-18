char * func0(int a,int b,int c)

{
  int c_local;
  int b_local;
  int a_local;
  char *local_10;
  
  if (b * b - a * 4 * c < 1) {
    if (b * b - a * 4 * c == 0) {
      local_10 = "1 solution";
    }
    else {
      local_10 = "No solutions";
    }
  }
  else {
    local_10 = "2 solutions";
  }
  return local_10;
}