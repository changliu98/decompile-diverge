int func0(int list1[], int n) {
  int first_even = -1;
  int first_odd = -1;
  for (int i = 0; i < n; i++) {
    if (list1[i] % 2 == 0 && first_even == -1) {
      first_even = list1[i];
    }
    if (list1[i] % 2 != 0 && first_odd == -1) {
      first_odd = list1[i];
    }
    if (first_even != -1 && first_odd != -1) {
      break;
    }
  }
  return first_even * first_odd;
}