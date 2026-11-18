double lagrange4(double *t, float *q, double time)
{
  double L;

  L = q[0]*(time-t[1])*(time-t[2])*(time-t[3])/((t[0]-t[1])*(t[0]-t[2])*(t[0]-t[3])) +
      q[1]*(time-t[0])*(time-t[2])*(time-t[3])/((t[1]-t[0])*(t[1]-t[2])*(t[1]-t[3])) +
      q[2]*(time-t[0])*(time-t[1])*(time-t[3])/((t[2]-t[0])*(t[2]-t[1])*(t[2]-t[3])) +
      q[3]*(time-t[0])*(time-t[1])*(time-t[2])/((t[3]-t[0])*(t[3]-t[1])*(t[3]-t[2]));

  return L;
}