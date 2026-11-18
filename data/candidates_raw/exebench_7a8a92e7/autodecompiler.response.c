void MxV( double *M, long *v, double *r )
{
 r[0] = M[0]*v[0] + M[3]*v[1] + M[6]*v[2];
 r[1] = M[1]*v[0] + M[4]*v[1] + M[7]*v[2];
 r[2] = M[2]*v[0] + M[5]*v[1] + M[8]*v[2];
}