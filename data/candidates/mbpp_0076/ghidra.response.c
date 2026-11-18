int func0(int m,int n)

{
  int temp;
  int n_local;
  int m_local;
  
  n_local = n;
  m_local = m;
  if (n < m) {
    n_local = m;
    m_local = n;
  }
  return (m_local * (m_local + 1) * (m_local * 2 + 1)) / 6 +
         ((n_local - m_local) * m_local * (m_local + 1)) / 2;
}