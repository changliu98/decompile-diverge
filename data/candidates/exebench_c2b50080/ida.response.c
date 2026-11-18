double __cdecl lagrange4(double *temp, float *q, double t)
{
  return *q
       * (t - temp[1])
       * (t - temp[2])
       * (t - temp[3])
       / ((*temp - temp[1])
        * (*temp - temp[2])
        * (*temp - temp[3]))
       + q[1]
       * (t - *temp)
       * (t - temp[2])
       * (t - temp[3])
       / ((temp[1] - *temp)
        * (temp[1] - temp[2])
        * (temp[1] - temp[3]))
       + q[2]
       * (t - *temp)
       * (t - temp[1])
       * (t - temp[3])
       / ((temp[2] - *temp)
        * (temp[2] - temp[1])
        * (temp[2] - temp[3]))
       + q[3]
       * (t - *temp)
       * (t - temp[1])
       * (t - temp[2])
       / ((temp[3] - *temp)
        * (temp[3] - temp[1])
        * (temp[3] - temp[2]));
}