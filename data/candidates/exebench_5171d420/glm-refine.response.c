// Assuming this is a fixed-point math system where 1024 represents 1.0
#define FIXED_POINT_SCALE 1024
#define FIXED_POINT_ONE   0x100000 // 1048576

int __cdecl inverse_rot(const int *m, int *o)
{
  // Check for division by zero in the original matrix's sine components
  if ( !m[1] || !m[2] )
    return 1; // Failure: Invalid input matrix

  // Calculate the inverse of the sine components
  // (Using fixed-point arithmetic: inverse = 1.0 / value)
  o[0] = 0;
  o[1] = FIXED_POINT_ONE / m[2];
  o[2] = FIXED_POINT_ONE / m[1];
  o[3] = 0;

  // Calculate the inverse translation components
  // Math equivalent: o[4] = -(o[2] * m[5]) / 1.0
  o[4] = -(o[2] * m[5]) / FIXED_POINT_SCALE;
  
  // Math equivalent: o[5] = -(o[1] * m[4]) / 1.0
  o[5] = -(o[1] * m[4]) / FIXED_POINT_SCALE;

  return 0; // Success
}