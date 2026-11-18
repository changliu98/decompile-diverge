void mat_trans_vec(float *out, float *mat, float *in)
{
  out[0] = mat[0]*in[0] + mat[4]*in[1] + mat[8]*in[2] + mat[12];
  out[1] = mat[1]*in[0] + mat[5]*in[1] + mat[9]*in[2] + mat[13];
  out[2] = mat[2]*in[0] + mat[6]*in[1] + mat[10]*in[2] + mat[14];
}