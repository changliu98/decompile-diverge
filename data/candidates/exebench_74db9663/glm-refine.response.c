Pointer to the destination where the result will be stored
void __cdecl zadd(double *x, double *y, double *u)
{
  // Add the real parts (or x-axis components)
  u[0] = x[0] + y[0];
  
  // Add the imaginary parts (or y-axis components)
  u[1] = x[1] + y[1];
}