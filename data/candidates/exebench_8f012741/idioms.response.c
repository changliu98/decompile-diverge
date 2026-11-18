void lin_solve_2(double *vec, double *mat, double *invec)
{
  double det = 1.0 / (mat[0]*mat[3] - mat[1]*mat[2]);
  vec[0] = det * (invec[1]*mat[3] - invec[0]*mat[1]);
  vec[1] = det * (invec[0]*mat[0] - invec[1]*mat[2]);
}