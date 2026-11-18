int func0(int *coins,int m,int V)

{
  int iVar1;
  int sub_res;
  int i;
  int res;
  int V_local;
  int m_local;
  int *coins_local;
  int local_c;
  
  if (V == 0) {
    local_c = 0;
  }
  else {
    res = 0x7fffffff;
    for (i = 0; i < m; i = i + 1) {
      if (((coins[i] <= V) && (iVar1 = func0(coins,m,V - coins[i]), iVar1 != 0x7fffffff)) &&
         (iVar1 + 1 < res)) {
        res = iVar1 + 1;
      }
    }
    local_c = res;
  }
  return local_c;
}