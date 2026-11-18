void cftf040(struct fcomplex *a)
{
  struct fcomplex tmp1; struct fcomplex tmp2; struct fcomplex tmp3; struct fcomplex tmp4;
  tmp1.real = a->real + a->imag;
  tmp1.imag = a->imag + a->real;
  tmp2.real = a->real - a->imag;
  tmp2.imag = a->imag - a->real;
  tmp3.real = a->imag + a->real;
  tmp3.imag = a->real - a->imag;
  tmp4.real = a->imag - a->real;
  tmp4.imag = a->real + a->imag;
  a->real = tmp1.real + tmp3.real;
  a->imag = tmp1.imag + tmp3.imag;
  a->imag = tmp2.real - tmp4.imag;
  a->real = tmp2.imag + tmp4.real;
  a->real = tmp1.real - tmp3.real;
  a->imag = tmp1.imag - tmp3.imag;
  a->imag = tmp2.real + tmp4.imag;
  a->real = tmp2.imag - tmp4.real;
}