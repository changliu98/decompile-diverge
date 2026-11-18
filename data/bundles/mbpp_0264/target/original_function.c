double func0(int h_age) {
  double d_age;
  if (h_age < 0) {
    exit(EXIT_FAILURE);
  } else if (h_age <= 2) {
    d_age = h_age * 10.5;
  } else {
    d_age = 21 + (h_age - 2) * 4;
  }
  return d_age;
}