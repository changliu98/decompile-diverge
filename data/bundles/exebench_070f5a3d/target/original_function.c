static inline void cpy3(double a[3], double b[3])
{
  do { *b++ = *a++; *b++ = *a++; *b++ = *a++; } while(0);
}