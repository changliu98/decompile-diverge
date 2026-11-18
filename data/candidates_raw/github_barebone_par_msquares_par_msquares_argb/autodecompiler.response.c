static int get_int(unsigned char *buf, int len)
{
 int i, ret, val = 0;

 if (len == 4) {
  val |= buf[2];
  val |= buf[1] << 8;
  val |= buf[0] << 16;
  val |= buf[3] << 24;
  ret = val;
 } else {
  for (i = 0;; i++) {
   if (i >= len)
    break;
   val <<= 8;
   val |= buf[i];
  }
  ret = val;
 }

 return ret;
}