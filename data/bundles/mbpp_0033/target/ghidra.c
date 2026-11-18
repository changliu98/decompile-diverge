int func0(int N)

{
  int i;
  int c;
  int rem;
  int cnt;
  int B_Number;
  int N_local;
  
  B_Number = 0;
  cnt = 0;
  for (N_local = N; N_local != 0; N_local = N_local / 2) {
    c = 1;
    for (i = 0; i < cnt; i = i + 1) {
      c = c * 10;
    }
    B_Number = (N_local % 2) * c + B_Number;
    cnt = cnt + 1;
  }
  return B_Number;
}