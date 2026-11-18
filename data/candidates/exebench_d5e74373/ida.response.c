int __cdecl obdRevConvert_3C_3F(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  float vala; // [rsp+24h] [rbp-4h]

  vala = 10.0 * (float)(val + 40.0);
  *A = (unsigned int)(int)vala / 256LL;
  *B = (unsigned int)(int)vala % 256LL;
  return 2;
}