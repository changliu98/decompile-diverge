void peneira(int m,int *v)

{
  int iVar1;
  int t;
  int f;
  int p;
  int *v_local;
  int m_local;
  
  p = 1;
  f = 2;
  iVar1 = v[1];
  for (; f <= m; f = f << 1) {
    if ((f < m) && (v[f] < v[f + 1])) {
      f = f + 1;
    }
    if (v[f] <= iVar1) break;
    v[p] = v[f];
    p = f;
  }
  v[p] = iVar1;
  return;
}