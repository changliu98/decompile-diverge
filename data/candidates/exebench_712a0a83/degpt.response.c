// Advances the motor position counter by 1, wrapping around at 0x3d (61)
void advance_m1pos(int *motor_position)
{
  // Increment the position and apply modulo 0x3d to keep it within bounds
  *motor_position = (*motor_position + 1) % 0x3d;
}