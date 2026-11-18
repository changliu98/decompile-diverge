bool _is_two_of_three_equal(int a, int b, int c) {
  if (a == b) {
    return true;
  } else if (b == c) {
    return true;
  } else if (c == a) {
    return true;
  } else {
    return false;
  }
}