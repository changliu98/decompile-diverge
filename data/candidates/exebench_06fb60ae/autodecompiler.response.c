void icvDetMatrix3x3_64d(const double m[9], double *result)
{
  *result = m[0] * (m[4]*m[8] - m[5]*m[7]) -
            m[1] * (m[3]*m[8] - m[5]*m[6]) +
            m[2] * (m[3]*m[7] - m[4]*m[6]);
}