static void
coap_option_nibble(unsigned int len, char *buf)
{
 if (len < 14) {
  buf[0] = len & 0xff;
  return;
 }
 if (len <= 268) {
  buf[0] = 13;
 } else if (len <= 66028) {
  buf[0] = 14;
 }
}