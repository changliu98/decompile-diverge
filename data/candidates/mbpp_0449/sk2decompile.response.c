char* _get_state(int x, int y, int z, int x1, int y1, int z1) {
  int result = (y1 * (y - z) + x1 * (z - y1) + x * (y1 - y));
  if (result == 0) {
    return "ON";
  } else {
    return "OFF";
  }
}