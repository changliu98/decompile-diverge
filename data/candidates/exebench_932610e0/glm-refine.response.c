double __cdecl randlc(double *x, double *a)
{
  // Cast the double values pointed to by 'a' and 'x' to 32-bit integers,
  // multiply them, and cast the result back to a double.
  double state = (double)((int)*a * (int)*x);
  
  // Update the state variable pointed to by 'x'
  *x = state;
  
  // Return the state multiplied by the constant 2^-46 (1.4210854715202e-14)
  return state * 1.4210854715202e-14;
}