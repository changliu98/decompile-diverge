int func0(int *list1,int size)

{
  int i_1;
  int i;
  int first_odd;
  int first_even;
  int size_local;
  int *list1_local;
  
  first_even = -1;
  first_odd = -1;
  for (i = 0; i < size; i = i + 1) {
    if (list1[i] % 2 == 0) {
      first_even = list1[i];
      break;
    }
  }
  i_1 = 0;
  do {
    if (size <= i_1) {
LAB_00101283:
      return first_even - first_odd;
    }
    if (list1[i_1] % 2 != 0) {
      first_odd = list1[i_1];
      goto LAB_00101283;
    }
    i_1 = i_1 + 1;
  } while( true );
}