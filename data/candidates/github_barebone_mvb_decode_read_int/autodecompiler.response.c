int
read_int(unsigned char *p, u_int64_t *v)
{
 int i;

 *v = p[0] & 0x7f;
 if (p[0] < 0x80) {
  i = 1;
 } else {
  *v |= (u_int64_t)(p[1] & 0x7f) << 7;
  if (p[1] < 0x80) {
   i = 2;
  } else {
   *v |= (u_int64_t)(p[2] & 0x7f) << 14;
   if (p[2] < 0x80) {
    i = 3;
   } else {
    *v |= (u_int64_t)(p[3] & 0x7f) << 21;
    if (p[3] < 0x80) {
     i = 4;
    } else {
     *v |= (u_int64_t)(p[4] & 0x7f) << 28;
     if (p[4] < 0x80) {
      i = 5;
     } else {
      *v |= (u_int64_t)(p[5] & 0x7f) << 35;
      if (p[5] < 0x80) {
       i = 6;
      } else {
       *v |= (u_int64_t)(p[6] & 0x7f) << 42;
       if (p[6] < 0x80) {
        i = 7;
       } else {
        *v |= (u_int64_t)(p[7] & 0x7f) << 49;
        if (p[7] < 0x80) {
         i = 8;
        } else {
         *v |= (u_int64_t)(p[8] & 0x7f) << 56;
         i = 9;
        }
       }
      }
     }
    }
   }
  }
 }

 if (i == 9 && p[8] > 0x01)
  return -1;

 return i;
}