int read_varint(unsigned char *buf, uint64_t *val, uint64_t *sum)
{
 int i;

 *val = buf[0] & 0x7f;
 if (buf[0] < 0x80) {
  *sum += *val;
  *val = *sum;
  i = 1;
 } else {
  *val |= (uint64_t)(buf[1] & 0x7f) << 7;
  if (buf[1] < 0x80) {
   *sum += *val;
   *val = *sum;
   i = 2;
  } else {
   *val |= (uint64_t)(buf[2] & 0x7f) << 14;
   if (buf[2] < 0x80) {
    *sum += *val;
    *val = *sum;
    i = 3;
   } else {
    *val |= (uint64_t)(buf[3] & 0x7f) << 21;
    if (buf[3] < 0x80) {
     *sum += *val;
     *val = *sum;
     i = 4;
    } else {
     *val |= (uint64_t)(buf[4] & 0x7f) << 28;
     *sum += *val;
     *val = *sum;
     i = 5;
    }
   }
  }
 }

 return i;
}