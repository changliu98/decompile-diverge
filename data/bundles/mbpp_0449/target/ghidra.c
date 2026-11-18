char * func0(int x1,int y1,int x2,int y2,int x3,int y3)

{
  int a;
  int y3_local;
  int x3_local;
  int y2_local;
  int x2_local;
  int y1_local;
  int x1_local;
  char *local_10;
  
  if (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2) == 0) {
    local_10 = "No";
  }
  else {
    local_10 = "Yes";
  }
  return local_10;
}