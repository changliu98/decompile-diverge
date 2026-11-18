void ComputeReverb16(short *in, short *out, long count, long level) {
  long temp;
  while (count-- > 0) {
    temp = *in++ * level / 100;
    temp += *out;
    if (temp > 32767)
      temp = 32767;
    else if (temp < -32767)
      temp = -32767;
    *out++ = (short)temp;
  }
}