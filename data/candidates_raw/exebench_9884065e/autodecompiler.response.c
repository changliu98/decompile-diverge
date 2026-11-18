char *decode_utf8(char *buf, int *ch)
{
 char *next;
 if ((buf[0] & 0xe0) == 0xc0 && (((buf[1]) & 0xc0) == 0x80)) {
  *ch = ((buf[0] & 0x1f) << 6) | ((buf[1] & 0x3f) << 0);
  next = buf + 2;
 } else if ((buf[0] & 0xf0) == 0xe0 && (((buf[1]) & 0xc0) == 0x80) && (((buf[2]) & 0xc0) == 0x80)) {
  *ch = ((buf[0] & 0x0f) << 12) | ((buf[1] & 0x3f) << 6) | ((buf[2] & 0x3f) << 0);
  next = buf + 3;
 } else if ((buf[0] & 0xf8) == 0xf0 && (((buf[1]) & 0xc0) == 0x80) && (((buf[2]) & 0xc0) == 0x80) && (((buf[3]) & 0xc0) == 0x80)) {
  *ch = ((buf[0] & 0x07) << 18) | ((buf[1] & 0x3f) << 12) | ((buf[2] & 0x3f) << 6) | ((buf[3] & 0x3f) << 0);
  next = buf + 4;
 } else if ((buf[0] & 0xfc) == 0xf8 && (((buf[1]) & 0xc0) == 0x80) && (((buf[2]) & 0xc0) == 0x80) && (((buf[3]) & 0xc0) == 0x80) && (((buf[4]) & 0xc0) == 0x80)) {
  *ch = ((buf[0] & 0x03) << 24) | ((buf[1] & 0x3f) << 18) | ((buf[2] & 0x3f) << 12) | ((buf[3] & 0x3f) << 6) | ((buf[4] & 0x3f) << 0);
  next = buf + 5;
 } else if ((buf[0] & 0xfe) == 0xfc && (((buf[1]) & 0xc0) == 0x80) && (((buf[2]) & 0xc0) == 0x80) && (((buf[3]) & 0xc0) == 0x80) && (((buf[4]) & 0xc0) == 0x80) && (((buf[5]) & 0xc0) == 0x80)) {
  *ch = ((buf[0] & 0x01) << 30) | ((buf[1] & 0x3f) << 24) | ((buf[2] & 0x3f) << 18) | ((buf[3] & 0x3f) << 12) | ((buf[4] & 0x3f) << 6) | ((buf[5] & 0x3f) << 0);
  next = buf + 6;
 } else {
  *ch = buf[0] & 0xff;
  next = buf + 1;
 }
 return next;
}