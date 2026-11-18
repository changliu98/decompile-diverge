short interpolate(WavData *wavData, short *buffer, int sample, int channel) {
  int result = 0;
  int index = (wavData->sampleRate + 1) * channel;
  int offset = wavData->sampleCount * sample;
  int start = index - offset - 1;
  int end = index - offset;
  int overflow = 0;
  int i;
  for (i = 0; i < 12; i++) {
    int coefficient = findSincCoefficient(i, start, end);
    int sampleValue = buffer[i * wavData->channelCount];
    int sampleResult = coefficient * sampleValue;
    int sign = getSign(result);
    result += sampleResult;
    if (getSign(result) != sign && getSign(sampleResult) == sign) {
      overflow += sign;
    }
  }
  if (overflow > 0) {
    return 32767;
  } else if (overflow < 0) {
    return -32768;
  } else {
    return result >> 16;
  }
}