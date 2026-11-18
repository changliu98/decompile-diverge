void ComputeReverb16(short *src, short *dst, long length, long strength) {
 long val;
 long max_val = 32767;
 long min_val = -32767;

 while (length-- > 0) {
  val = *dst + (((long)(*src++) * strength) / 100);
  if (val > max_val)
   val = max_val;
  else if (val < min_val)
   val = min_val;
  *dst++ = val;
 }
}