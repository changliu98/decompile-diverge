int func0(int *list, int size){
  int first_even = -1;
  int first_odd = -1;
  int i;
  for (i = 0; i < size; i++)
    if (list[i] % 2 == 0) {
      first_even = list[i];
      break;
    }
  for (i = 0; i < size; i++)
    if (list[i] % 2 == 1) {
      first_odd = list[i];
      break;
    }
  return first_even + first_odd;
}