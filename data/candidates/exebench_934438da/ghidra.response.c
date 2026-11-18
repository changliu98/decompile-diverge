void testfunc16(int *p1,int *p2,int *p3,int *p4,int *p5)

{
  int *p5_local;
  int *p4_local;
  int *p3_local;
  int *p2_local;
  int *p1_local;
  
  p2[1] = p2[1] + 100;
  *(char *)p4 = (char)*p4 + (char)p4;
  return;
}