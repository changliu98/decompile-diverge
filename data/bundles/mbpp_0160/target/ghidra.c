char * func0(int a,int b,int n)

{
  int i;
  int n_local;
  int b_local;
  int a_local;
  
  i = 0;
  while( true ) {
    if (n < i * a) {
      return "No solution";
    }
    if ((n - i * a) % b == 0) break;
    i = i + 1;
  }
  sprintf(func0::result,"x = %d, y = %d",(ulong)(uint)i,(long)(n - i * a) / (long)b & 0xffffffff);
  return func0::result;
}