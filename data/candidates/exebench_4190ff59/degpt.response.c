// Decrements the current motor value by 0x80 to control backward movement
void motorctrl_backward(int *current_motor_value)
{
  *current_motor_value -= 0x80;
}