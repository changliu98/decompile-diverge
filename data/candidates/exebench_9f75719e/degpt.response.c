// Advances the motor control value by 0x80 to move the motor forward.
void motorctrl_forward(int *current_motor_value)
{
  // Increment the current motor value by 0x80.
  *current_motor_value += 0x80;
}