float ramp_activate(float x) {
  float y;
  if (x > 0) {
    y = 0.1 * x;
  } else {
    y = 0;
  }
  return y + 0.1 * x;
}