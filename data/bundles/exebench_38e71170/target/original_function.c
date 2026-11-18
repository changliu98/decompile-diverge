static inline void scal3(double scal, double* v)
{
  do { *v++ *= scal; *v++ *= scal; *v++ *= scal; } while(0);
}