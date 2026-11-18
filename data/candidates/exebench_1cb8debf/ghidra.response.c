void sBitwiseXor_process(float bIn0,float bIn1,float *bOut)

{
  float *bOut_local;
  float bIn1_local;
  float bIn0_local;
  
  *bOut = (float)((int)bIn0 ^ (int)bIn1);
  return;
}