int sboxCHECK(float *lb,float *ub,int m)

{
  int i;
  int m_local;
  float *ub_local;
  float *lb_local;
  
  if ((lb != (float *)0x0) && (ub != (float *)0x0)) {
    for (i = 0; i < m; i = i + 1) {
      if (ub[i] <= lb[i] && lb[i] != ub[i]) {
        return 0;
      }
    }
  }
  return 1;
}