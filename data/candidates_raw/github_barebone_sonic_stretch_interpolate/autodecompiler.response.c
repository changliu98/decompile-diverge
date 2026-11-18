int16_t computeOutputSample(
  struct SoundDriver *self,
  short *buffer,
  int oldSampleRate,
  int newSampleRate)
{
  int total = 0;
  int position = self->sampleOffset * oldSampleRate;
  int leftPosition = self->currentSample * newSampleRate;
  int rightPosition = (self->currentSample + 1) * newSampleRate;
  int ratio = rightPosition - position - 1;
  int width = rightPosition - leftPosition;
  int overflowCount = 0;

  int i = 0;
  while (true)
  {
    if (i < 13)
    {
      int weight = findSincCoefficient(i, ratio, width);
      int sample = buffer[i * self->channels] * weight;

      int oldSign = getSign(total);
      total += sample;

      int newSign = getSign(total);

      if (oldSign != newSign && getSign(sample) == oldSign)
        overflowCount += oldSign;

      i++;
    }
    else
      break;
  }

  int16_t result;

  if (overflowCount > 0)
    result = 32767;
  else if (overflowCount < 0)
    result = -32768;
  else
  {
    while (true)
    {
      if (total >= 32768)
      {
        result = 32767;
        break;
      }
      else if (total <= -32769)
      {
        result = -32768;
        break;
      }
      else
      {
        result = total >> 16;
        break;
      }
    }
  }

  return result;
}