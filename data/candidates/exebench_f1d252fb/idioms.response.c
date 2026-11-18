void endian_swap16bit(void *x)
{
  __asm__ __volatile__ (
  "movw  %%ax,%%dx\n\t"
  "bswap %%ax\n\t"
  "movw  %%ax,%%dx\n\t"
  :"=a"(*(unsigned short *)x)
  :"0"(*(unsigned short *)x));
}