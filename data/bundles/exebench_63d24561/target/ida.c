int __cdecl zmlt_(double *ar, double *ai, double *br, double *bi, double *cr, double *ci)
{
  double cb; // [rsp+0h] [rbp-40h]

  cb = *ar * *bi + *ai * *br;
  *cr = *ar * *br - *ai * *bi;
  *ci = cb;
  return 0;
}