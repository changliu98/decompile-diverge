void __cdecl icvDetMatrix3x3_64d(const double *mat, double *det)
{
  *det = mat[2] * (mat[3] * mat[7] - mat[4] * mat[6])
       + *mat * (mat[4] * mat[8] - mat[5] * mat[7])
       - mat[1] * (mat[3] * mat[8] - mat[5] * mat[6]);
}