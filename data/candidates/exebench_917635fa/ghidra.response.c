void adders_io(int in1,int in2,int *in_out1)

{
  int *in_out1_local;
  int in2_local;
  int in1_local;
  
  *in_out1 = in1 + in2 + *in_out1;
  return;
}