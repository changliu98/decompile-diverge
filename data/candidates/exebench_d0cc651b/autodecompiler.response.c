void increment(int *byte) {
 int carry = 1;
 int bit = *byte;
 int mask = 1;

 while (1) {
  if ((bit & mask) == 0) {
   bit ^= mask;
   break;
  } else {
   bit ^= mask;
   mask <<= 1;
  }
 }

 *byte = bit ^ mask;
}