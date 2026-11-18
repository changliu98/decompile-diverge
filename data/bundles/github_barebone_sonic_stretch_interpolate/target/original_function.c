static short interpolate(sonicStream stream, short* in, int oldSampleRate,
                         int newSampleRate) {
  /* Compute N-point sinc FIR-filter here.  Clip rather than overflow. */
  int i;
  int total = 0;
  int position = stream->newRatePosition * oldSampleRate;
  int leftPosition = stream->oldRatePosition * newSampleRate;
  int rightPosition = (stream->oldRatePosition + 1) * newSampleRate;
  int ratio = rightPosition - position - 1;
  int width = rightPosition - leftPosition;
  int weight, value;
  int oldSign;
  int overflowCount = 0;

  for (i = 0; i < SINC_FILTER_POINTS; i++) {
    weight = findSincCoefficient(i, ratio, width);
    value = in[i * stream->numChannels] * weight;
    oldSign = getSign(total);
    total += value;
    if (oldSign != getSign(total) && getSign(value) == oldSign) {
      /* We must have overflowed.  This can happen with a sinc filter. */
      overflowCount += oldSign;
    }
  }
  /* It is better to clip than to wrap if there was a overflow. */
  if (overflowCount > 0) {
    return SHRT_MAX;
  } else if (overflowCount < 0) {
    return SHRT_MIN;
  }
  return total >> 16;
}