int func0(int A,int N,int L,int R)

{
  int i;
  int count;
  int R_local;
  int L_local;
  int N_local;
  int A_local;
  
  count = 0;
  i = L;
  while( true ) {
    if (R < i) {
      return i;
    }
    if (i % A != 0) {
      count = count + 1;
    }
    if (count == N) break;
    i = i + 1;
  }
  return i;
}