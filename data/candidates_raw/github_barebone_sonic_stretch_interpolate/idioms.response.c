static short processSample(struct SonicStream *stream, short *in, int oldSampleRate, int newSampleRate)
{
  int i;
  int total = 0;
  int rightPosition = (stream->oldRatePosition + 1) * newSampleRate;
  int ratio = rightPosition - (oldSampleRate * stream->newRatePosition) - 1;
  int width = rightPosition - (stream->oldRatePosition * newSampleRate);
  int overflowCount = 0;
  for (i = 0; i < 12; i++)
  {
    int value = in[i * stream->numChannels] * getSample(i, ratio, width);
    int oldSign = getSign(total);
    total += value;
    if (getSign(total) != oldSign && getSign(value) == oldSign)
    {
      overflowCount += oldSign;
    }
  }
  if (overflowCount > 0)
  {
    return 32767;
  }
  if (overflowCount < 0)
  {
    return -32768;
  }
  return (total >> 16);
}