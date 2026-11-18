void motorctrl_forward(int *speed) {
  *speed = *speed + 128;
  if (*speed > 255) {
    *speed = 255;
  }
}