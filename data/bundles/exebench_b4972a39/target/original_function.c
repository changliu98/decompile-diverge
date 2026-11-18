static inline void sub3x3(double a[9], double b[9])
{
  do { *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; *b++ -= *a++; } while(0);
}