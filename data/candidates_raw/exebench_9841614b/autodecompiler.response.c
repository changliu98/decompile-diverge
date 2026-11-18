static int
is_smi_nibble(unsigned int val, unsigned int *byte, int *shift)
{
 int ret;
 int nibble;

 if (val == 0) {
  *byte = 0;
  *shift = 0;
  ret = 1;
 } else {
  nibble = 0;
  while (1) {
   if (nibble < 16) {
    if ((val & 3) != 0 && val < 256) {
     *byte = val;
     *shift = nibble;
     ret = 1;
     break;
    }
    if ((val & 3) != 0) {
     ret = 0;
     break;
    }
    val >>= 2;
    nibble++;
   } else {
    ret = 0;
    break;
   }
  }
 }
 return ret;
}