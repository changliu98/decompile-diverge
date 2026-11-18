static int alps_check_valid_firmware_id(unsigned char *buf)
{
 int ret;

 if ((buf[0] == 0x73)) {
  ret = 1;
 } else if ((buf[0] == 0x88) && ((buf[1] == 0x07) || (buf[1] == 0x08) ||
  ((buf[1] & 0xf0) == 0xb0) || ((buf[1] & 0xf0) == 0xc0))) {
  ret = 1;
 } else {
  ret = 0;
 }

 return ret;
}