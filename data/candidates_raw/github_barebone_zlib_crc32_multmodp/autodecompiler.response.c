unsigned long crc32(unsigned long crc, unsigned long data)
{
 unsigned long mask;
 unsigned long result;

 result = 0;
 for (mask = 1UL << 31; mask != 0; mask >>= 1) {
  if ((crc & mask) != 0) {
   result ^= data;
   if ((data & 1) != 0) {
    data >>= 1;
    data ^= 0xEDB88320;
   } else {
    data >>= 1;
   }
  } else {
   mask >>= 1;
   if ((data & 1) != 0) {
    data >>= 1;
    data ^= 0xEDB88320;
   } else {
    data >>= 1;
   }
  }
 }
 return result;
}