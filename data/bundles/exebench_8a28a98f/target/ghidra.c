char * itoa(int value,char *str,int base)

{
  char cVar1;
  char *pcVar2;
  char tmp;
  char *low;
  char *ptr;
  char *rc;
  int base_local;
  char *str_local;
  int value_local;
  
  if ((base < 2) || (pcVar2 = str, value_local = value, 0x24 < base)) {
    *str = '\0';
  }
  else {
    do {
      ptr = pcVar2;
      *ptr = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"
             [value_local % base + 0x23];
      value_local = value_local / base;
      pcVar2 = ptr + 1;
    } while (value_local != 0);
    ptr[1] = '\0';
    low = str;
    while (low < ptr) {
      cVar1 = *low;
      *low = *ptr;
      *ptr = cVar1;
      low = low + 1;
      ptr = ptr + -1;
    }
  }
  return str;
}