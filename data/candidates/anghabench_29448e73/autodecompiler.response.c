static int hex_to_int(char *hex, int *val)
{
 int i;
 int ret;

 *val = 0;
 for (i = 0;; i++) {
  if (i >= 9) {
   ret = 1;
   break;
  }
  if ((hex[i] >= '0') && (hex[i] <= '9')) {
   *val = (*val << 4) + hex[i] - '0';
  } else if ((hex[i] >= 'a') && (hex[i] <= 'f')) {
   *val = (*val << 4) + hex[i] - 'a' + 10;
  } else {
   ret = 0;
   break;
  }
 }

 return ret;
}