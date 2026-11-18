int func0(int n,int m)

{
  int local_1c;
  int b;
  int a;
  int m_local;
  int n_local;
  
  local_1c = (n / m) * m;
  if ((local_1c + m) - n < n - local_1c) {
    local_1c = local_1c + m;
  }
  return local_1c;
}