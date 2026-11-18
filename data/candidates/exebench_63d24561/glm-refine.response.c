int __cdecl zmlt_(double *ar, double *ai, double *br, double *bi, double *cr, double *ci)
{
  double imag = *ar * *bi + *ai * *br;
  *cr = *ar * *br - *ai * *bi;
  *ci = imag;
  return 0;
}