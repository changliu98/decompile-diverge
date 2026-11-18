int mode1112(int c,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8)

{
  int val;
  int sum;
  int a5_local;
  int a4_local;
  int a3_local;
  int a2_local;
  int a1_local;
  int c_local;
  
  return c * 4 + (a2 + a4 + a5 + a7) * 2 + a1 + a3 + a6 + a8 + 8 >> 4;
}