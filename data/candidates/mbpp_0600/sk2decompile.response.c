bool _is_next_state(int state) {
  int next_state = state ^ 1;
  if (next_state == state + 1) {
    return true;
  } else {
    return false;
  }
}