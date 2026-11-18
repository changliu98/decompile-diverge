bool _is_opposite_direction(int direction) {
  int opposite_direction = direction ^ 1;
  if (opposite_direction == direction - 1) {
    return true;
  } else {
    return false;
  }
}