void vec_mul_so3( float scalar,
    float *v1,
    float *vout )
{
  int k ;

  for (k=0; k<4; k++)
    vout[k] = scalar*v1[k] ;
}