void denormF(double *pr, double *ucon, double *ucov)
{
  double u0, u1, u2 ;

  u0 = ucov[0] ;
  u1 = ucov[1] ;
  u2 = ucov[2] ;

  pr[6] += pr[0]*u1 + pr[3]*u2 ;
  pr[7] += pr[1]*u1 + pr[4]*u2 ;
  pr[8] += pr[2]*u1 + pr[5]*u2 ;

  pr[0] *= u0 ;
  pr[1] *= u0 ;
  pr[2] *= u0 ;
  pr[3] *= u0 ;
  pr[4] *= u0 ;
  pr[5] *= u0 ;

  u0 = ucon[0] ;
  u1 = ucon[1] ;
  u2 = ucon[2] ;

  pr[2] += pr[0]*u1 + pr[3]*u2 ;
  pr[5] += pr[3]*u1 + pr[4]*u2 ;
  pr[8] += pr[6]*u1 + pr[7]*u2 ;

  pr[0] *= u0 ;
  pr[3] *= u0 ;
  pr[6] *= u0 ;

  pr[1] *= u0 ;
  pr[4] *= u0 ;
  pr[7] *= u0 ;

}