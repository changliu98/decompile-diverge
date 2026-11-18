int sonicFindPeriod(struct sonicStream *stream, short *samples, int preferNewPeriod)
{
  int minPeriod; int maxPeriod; int minDiff; int maxDiff; int period; int retPeriod;
  int skip;
  minPeriod = stream->minPeriod;
  maxPeriod = stream->maxPeriod;
  skip = sonicGetSkip(stream, stream->sampleRate);
  if (stream->numChannels == 1 && skip == 1)
  {
    minPeriod = (int)(minPeriod * 1);
    maxPeriod = (int)(maxPeriod * 1);
  }
  else
  {
    sonicDownSample(stream, samples, skip);
    minPeriod = (int)(minPeriod / skip);
    maxPeriod = (int)(maxPeriod / skip);
    if (skip != 1)
    {
      minPeriod = (int)(minPeriod * skip);
      maxPeriod = (int)(maxPeriod * skip);
      minPeriod -= (int)(skip * 4);
      maxPeriod += (int)(skip * 4);
      if (minPeriod < stream->minPeriod)
        minPeriod = stream->minPeriod;
      if (maxPeriod > stream->maxPeriod)
        maxPeriod = stream->maxPeriod;
      if (stream->numChannels == 1)
      {
        minPeriod = (int)(minPeriod * 1);
        maxPeriod = (int)(maxPeriod * 1);
      }
      else
      {
        sonicDownSample(stream, samples, 1);
        minPeriod = (int)(minPeriod * 1);
        maxPeriod = (int)(maxPeriod * 1);
      }
    }
  }
  period = sonicFindPeriodInBlock(samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
  if (sonicIsPeriodInBlock(stream, minDiff, maxDiff, preferNewPeriod))
    retPeriod = stream->prevPeriod;
  else
    retPeriod = period;
  stream->prevMinDiff = minDiff;
  stream->prevPeriod = period;
  return retPeriod;
}