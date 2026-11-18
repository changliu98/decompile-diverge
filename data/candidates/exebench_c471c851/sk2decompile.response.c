void stb_linear_controller(float *value, float target, float rate, float dt,
                           float time_left) {
  float sign = 1.0f;
  float v = *value;
  if (v == target) return;
  if (v > target) {
    target = -target;
    v = -v;
    sign = -1.0f;
  }
  if (v < 0) {
    v += dt * time_left;
    if (v > 0) {
      v = 0;
      time_left -= v / dt;
      if (time_left < 0) time_left = 0;
    } else {
      time_left = 0;
    }
  }
  v += rate * time_left;
  if (v > target) v = target;
  *value = v * sign;
}