void ssm(short *in)
{
  int a0 = in[0]*W0 + in[4]*W0;
  int a1 = in[1]*W1 + in[7]*W7;
  int a2 = in[2]*W2 + in[6]*W6;
  int a3 = in[3]*W3 - in[5]*W5;
  int a4 = in[0]*W0 - in[4]*W0;
  int a5 = in[3]*W3 + in[5]*W5;
  int a6 = in[2]*W2 - in[6]*W2;
  int a7 = in[1]*W1 - in[7]*W1;
  int s1 = (a1 + a7 - a5 - a3)*181 + 128; s1 >>= 8;
  int s2 = (a1 + a3 - a5 - a7)*181 + 128; s2 >>= 8;
  in[0] = (a1 + a2 + a0 + a5 + 128)>>8;
  in[1] = (a1 + a6 + s1 + 128)>>8;
  in[2] = (a1 + a4 - s1 + 128)>>8;
  in[3] = (a1 + a3 + a0 - a2 + 128)>>8;
  in[4] = (a1 - a2 - a3 - a7 + 128)>>8;
  in[5] = (a1 + a4 - s2 + 128)>>8;
  in[6] = (a1 + a6 - s2 + 128)>>8;
  in[7] = (a1 + a0 - a1 - a5 + 128)>>8;
}