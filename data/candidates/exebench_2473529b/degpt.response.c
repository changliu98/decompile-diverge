void normalize_angle(double *angle)
{
  // Normalize angle to be within the range [0, 2*pi)
  // Subtract 2*pi until the angle is less than 2*pi
  while (*angle >= TWO_PI) {
    *angle -= TWO_PI;
  }
  // Add 2*pi until the angle is greater than or equal to 0
  while (*angle <= 0.0) {
    *angle += TWO_PI;
  }
}