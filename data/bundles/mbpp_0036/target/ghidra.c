int func0(int p,int q,int N)

{
  int res;
  int N_local;
  int q_local;
  int p_local;
  
  p_local = p;
  for (N_local = N; 0 < N_local; N_local = N_local + -1) {
    res = (p_local * 10) / q;
    p_local = (p_local * 10) % q;
  }
  return res;
}