void __cdecl swap_float_4(float *tnf4)
{
  unsigned int *v = (unsigned int *)tnf4;
  *v = ((*v & 0x0000FF00) << 8) | 
       ((*v & 0x00FF0000) >> 8) | 
       ((*v & 0x000000FF) << 24) | 
       ((*v & 0xFF000000) >> 24);
}