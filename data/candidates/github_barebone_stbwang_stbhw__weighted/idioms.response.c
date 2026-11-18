int stbhw__weighted(int num_options, int *weights)
{
  int total = 0;
  int i;
  for (i = 0; i < num_options; i++)
    total += weights[i];
  int choice = stbhw__rand() / 16 % total;
  total = 0;
  for (i = 0; i < num_options; i++) {
    total += weights[i];
    if (choice < total)
      break;
  }
  ((void) sizeof ((i < num_options) ? 1 : 0), __extension__ ({ if (i < num_options) ; else __assert_fail ("k < num_options", "func.c", 692, __extension__ __PRETTY_FUNCTION__); }));
  return i;
}