void lin_solve_3(double *out, double *in, double *invec)
{
  double det = in[0]*((in[4]*in[8])-(in[5]*in[7]))
    + in[1]*((in[5]*in[6])-(in[3]*in[8]))
    + in[2]*((in[3]*in[7])-(in[4]*in[6]));
  double invdet = 1.0/det;
  double inv0 = (in[4]*in[8])-(in[5]*in[7]);
  double inv1 = (in[5]*in[6])-(in[3]*in[8]);
  double inv2 = (in[3]*in[7])-(in[4]*in[6]);
  double inv3 = (in[1]*in[6])-(in[2]*in[7]);
  double inv4 = (in[2]*in[5])-(in[0]*in[8]);
  double inv5 = (in[0]*in[7])-(in[1]*in[6]);
  double inv6 = (in[0]*in[4])-(in[1]*in[3]);
  out[0] = invdet*((invec[0]*inv0)+(invec[1]*inv3)+(invec[2]*inv6));
  out[1] = invdet*((invec[0]*inv1)+(invec[1]*inv4)+(invec[2]*inv5));
  out[2] = invdet*((invec[0]*inv2)+(invec[1]*inv3)+(invec[2]*inv0));
}