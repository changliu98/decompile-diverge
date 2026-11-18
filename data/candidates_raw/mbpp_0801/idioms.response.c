int is_right(int a, int b, int c)
{
  int x = a; int y = b; int z = c;
  int result[3] = { a, b, c };
  int unique_values = 0;
  int counts[3] = { 0, 0, 0 };
  int i; int j; int found;
  for (i = 0; i < 3; i++) {
    found = 0;
    for (j = 0; j < i; j++) {
      if (result[j] == result[i]) {
        found = 1;
        break;
      }
    }
    if (found == 0) {
      unique_values++;
    }
  }
  if (unique_values == 3) {
    return 0;
  }
  return 4 - unique_values;
}