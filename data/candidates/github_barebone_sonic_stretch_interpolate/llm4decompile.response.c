short interpolate(
    sonicStream stream,
    short *in,
    int oldSampleRate,
    int newSampleRate)
{
    int newRatePosition = stream->newRatePosition;
    int oldRatePosition = stream->oldRatePosition;
    int oldRateIncrement = oldSampleRate;
    int newRateIncrement = newSampleRate;
    int halfWidth = 6;
    int width = halfWidth * 2;
    int i;
    int leftPosition = newRatePosition - halfWidth * newRateIncrement;
    int rightPosition = newRatePosition + halfWidth * newRateIncrement;
    int sample = 0;
    int sign = 0;
    int overflowCount = 0;

    for(i = 0; i < width; i++)
    {
 int coefficient = findSincCoefficient(i - halfWidth, rightPosition - newRatePosition, rightPosition - oldRatePosition);
 int oldSample = in[(i + oldRatePosition) * stream->numChannels];
 int oldSign = getSign(sample);
 sample += oldSample * coefficient;
 if(oldSign != getSign(sample))
 {
     if(oldSign == getSign(oldSample * coefficient))
     {
  overflowCount++;
     }
 }
    }
    if(overflowCount > 0)
    {
 sample = (sample < 0)? -32768: 32767;
    }
    else if(overflowCount < 0)
    {
 sample = (sample < 0)? -32769: 32768;
    }
    else
    {
 sample = sample >> 16;
    }
    return sample;
}