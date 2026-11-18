void TwoOutArgs(int a,int *pi,int b,int *pj)

{
  int *pj_local;
  int b_local;
  int *pi_local;
  int a_local;
  
  *pi = a + *pi;
  *pj = b + *pj;
  return;
}