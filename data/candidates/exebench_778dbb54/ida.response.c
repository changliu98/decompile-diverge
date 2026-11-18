int __cdecl obdRevConvert_43(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  float vala; // [rsp+24h] [rbp-4h]

  vala = (float)(255.0 * val) / 100.0;
  *A = (unsigned int)(int)vala / 256LL;
  *B = (unsigned int)(int)vala % 256LL;
  return 2;
}