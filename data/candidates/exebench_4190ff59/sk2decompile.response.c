void motorctrl_backward(int *speed) {
  *speed -= 128;
  if (*speed < 0) {
    *speed = 0;
  }
}