int findPitchPeriod(
    sonicStream stream,
    short *samples,
    int preferNewPeriod)
{
    int minPeriod = stream->minPeriod;
    int maxPeriod = stream->maxPeriod;
    int skip = computeSkip(stream, stream->sampleRate);
    int period, minDiff, maxDiff;

    if(stream->numChannels == 1 && skip == 1) {
 period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
    } else {
 downSampleInput(stream, samples, skip);
 period = findPitchPeriodInRange(stream->downSampleBuffer, minPeriod/skip, maxPeriod/skip,
     &minDiff, &maxDiff);
 if(skip != 1) {
     minPeriod = period*skip - 4*skip;
     maxPeriod = period*skip + 4*skip;
     if(minPeriod < stream->minPeriod) {
  minPeriod = stream->minPeriod;
     }
     if(maxPeriod > stream->maxPeriod) {
  maxPeriod = stream->maxPeriod;
     }
     if(stream->numChannels == 1) {
  period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
     } else {
  downSampleInput(stream, samples, 1);
  period = findPitchPeriodInRange(stream->downSampleBuffer, minPeriod, maxPeriod,
      &minDiff, &maxDiff);
     }
 }
    }
    if(!prevPeriodBetter(stream, minDiff, maxDiff, preferNewPeriod)) {
 period = stream->prevPeriod;
    }
    stream->prevMinDiff = minDiff;
    stream->prevPeriod = period;
    return period;
}