void matvec(int n, double *in, double *out, double *matr)
{
  double *in_ptr = in;
  double *out_ptr = out;
  double *matr_ptr = matr;
  while ( n > 0 )
  {
    *out_ptr = *out_ptr + ( *in_ptr++ * *matr_ptr++ );
    --n;
  }
}