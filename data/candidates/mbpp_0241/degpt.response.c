char *** func0(int m,int n,int o)

{
  char ***pppcVar1;
  char **ppcVar2;
  char *pcVar3;
  int k;
  int j;
  int i;
  char ***result;
  int o_local;
  int n_local;
  int m_local;
  
  pppcVar1 = malloc((long)o << 3);
  for (i = 0; i < o; i = i + 1) {
    ppcVar2 = malloc((long)n << 3);
    pppcVar1[i] = ppcVar2;
    for (j = 0; j < n; j = j + 1) {
      pcVar3 = malloc((long)m);
      pppcVar1[i][j] = pcVar3;
      for (k = 0; k < m; k = k + 1) {
        pppcVar1[i][j][k] = '*';
      }
    }
  }
  return pppcVar1;
}