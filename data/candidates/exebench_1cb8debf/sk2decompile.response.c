void sBitwiseXor_process(float in1, float in2, float *out) {
  int iin1 = (int)in1;
  int iin2 = (int)in2;
  int iout = iin1 ^ iin2;
  *out = (float)iout;
}