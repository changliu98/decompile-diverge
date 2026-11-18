short __cdecl interpolate(sonicStream stream, short *in, int oldSampleRate, int newSampleRate)
{
  int overflowCount; // [rsp+4h] [rbp-4Ch]
  int oldSign; // [rsp+8h] [rbp-48h]
  int value; // [rsp+Ch] [rbp-44h]
  int width; // [rsp+14h] [rbp-3Ch]
  int ratio; // [rsp+18h] [rbp-38h]
  int rightPosition; // [rsp+1Ch] [rbp-34h]
  int total; // [rsp+28h] [rbp-28h]
  int i; // [rsp+2Ch] [rbp-24h]

  total = 0;
  rightPosition = newSampleRate * (stream->oldRatePosition + 1);
  ratio = rightPosition - oldSampleRate * stream->newRatePosition - 1;
  width = rightPosition - newSampleRate * stream->oldRatePosition;
  overflowCount = 0;
  for ( i = 0; i < 12; ++i )
  {
    value = findSincCoefficient(i, ratio, width) * in[stream->numChannels * i];
    oldSign = getSign(total);
    total += value;
    if ( oldSign != getSign(total) && getSign(value) == oldSign )
      overflowCount += oldSign;
  }
  if ( overflowCount > 0 )
    return 0x7FFF;
  if ( overflowCount >= 0 )
    return HIWORD(total);
  return 0x8000;
}