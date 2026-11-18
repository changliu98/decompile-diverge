int getMax(int a,int b,int c,int *max)

{
  int tmpMax;
  int choice;
  int *max_local;
  int c_local;
  int b_local;
  int a_local;
  
  choice = 1;
  tmpMax = a;
  if (a < b) {
    choice = 2;
    tmpMax = b;
  }
  if (tmpMax < c) {
    choice = 3;
    tmpMax = c;
  }
  *max = tmpMax;
  return choice;
}