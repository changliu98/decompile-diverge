char *itoa(int value, char *string, int radix)
{
 char *buf_ptr, *tmp_ptr;
 char *ret_ptr;
 char digit;


 if ((radix < 2) || (radix > 36)) {
  *string = '\0';
  return string;
 }

 buf_ptr = tmp_ptr = ret_ptr = string;

 if (value < 0)
  *buf_ptr++ = '-';


 do {
  *buf_ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (value % radix)];
  value /= radix;
 } while (value != 0);
 *buf_ptr-- = '\0';


 while (tmp_ptr < buf_ptr) {
  digit = *tmp_ptr;
  *tmp_ptr++ = *buf_ptr;
  *buf_ptr-- = digit;
 }

 return ret_ptr;
}