int func0(int a,int b,int c)

{
  int median;
  int c_local;
  int b_local;
  int a_local;
  
  median = a;
  if (b < a) {
    if ((c <= a) && (median = c, c < b)) {
      median = b;
    }
  }
  else if ((a <= c) && (median = c, b < c)) {
    median = b;
  }
  return median;
}