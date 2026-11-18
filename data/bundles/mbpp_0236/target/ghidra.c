int func0(int N,int K)

{
  int Tri_down;
  int Tri_up;
  int K_local;
  int N_local;
  undefined4 local_c;
  
  if (N < K) {
    local_c = -1;
  }
  else {
    local_c = (((N - K) + 1) * ((N - K) + 2)) / 2 + ((N + K * -2 + 1) * (N + K * -2 + 2)) / 2;
  }
  return local_c;
}