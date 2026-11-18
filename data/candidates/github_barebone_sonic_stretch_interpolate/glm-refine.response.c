short __cdecl interpolate(sonicStream stream, short *in, int oldSampleRate, int newSampleRate)
{
  int overflowCount = 0;
  int total = 0;
  int oldSign;
  int value;
  int width;
  int ratio;
  int rightPosition;
  int i;

  rightPosition = newSampleRate * (stream->oldRatePosition + 1);
  ratio = rightPosition - oldSampleRate * stream->newRatePosition - 1;
  width = rightPosition - newSampleRate * stream->oldRatePosition;

  for (i = 0; i < 12; ++i)
  {
    value = findSincCoefficient(i, ratio, width) * in[stream->numChannels * i];
    oldSign = getSign(total);
    total += value;
    
    // Check for arithmetic overflow
    if (oldSign != getSign(total) && getSign(value) == oldSign)
      overflowCount += oldSign;
  }

  if (overflowCount > 0)
    return 0x7FFF;       // Positive overflow clamp (32767)
  if (overflowCount >= 0)
    return (short)(total >> 16); // HIWORD(total) - extract upper 16 bits
  return 0x8000;         // Negative overflow clamp (-32768)
}