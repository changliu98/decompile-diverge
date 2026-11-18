void array_are_reference_type(int *a) {
  int tmp;
  tmp = a[0];
  a[0] = a[1];
  a[1] = tmp;
}