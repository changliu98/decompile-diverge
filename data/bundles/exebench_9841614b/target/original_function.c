static inline int UnpackImmediate(unsigned int val, int* outByte, int* outShift) {
 if (val == 0) {
  *outByte = 0;
  *outShift = 0;
  return 1;
 }

 for (int i = 0; i < 15; i++) {
  if ((val & 3) && val < 256) {
   *outByte = val;
   *outShift = i;
   return 1;
  }
  else if (val & 3) {
   return 0;
  }
  val >>= 2;
 }

 return 0;
}