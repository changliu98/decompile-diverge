void rsVec_cross(float *out, float *in1, float *in2)
{
  out[0] = in1[1]*in2[2] + in1[2]*in2[1];
  out[1] = in1[2]*in2[0] + in1[0]*in2[2];
  out[2] = in1[0]*in2[1] + in1[1]*in2[0];
}