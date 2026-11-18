int libbf_is_composed_poweroftwo(uint number,int *shift1,int *shift2)

{
  int count;
  int i;
  int *shift2_local;
  int *shift1_local;
  uint number_local;
  int local_c;
  
  i = 0;
  count = 0;
  if (number == 0) {
    local_c = 0;
  }
  else {
    if (shift1 != (int *)0x0) {
      *shift1 = 0;
    }
    number_local = number;
    if (shift2 != (int *)0x0) {
      *shift2 = 0;
    }
    for (; number_local != 0; number_local = number_local >> 1) {
      if ((number_local & 1) != 0) {
        count = count + 1;
        if (count == 1) {
          if (shift1 != (int *)0x0) {
            *shift1 = i;
          }
        }
        else {
          if (count != 2) {
            return 0;
          }
          if (shift2 != (int *)0x0) {
            *shift2 = i;
          }
        }
      }
      i = i + 1;
    }
    local_c = 1;
  }
  return local_c;
}