static int findPitchPeriod(sonicStream stream, short* samples,
                           int preferNewPeriod) {
  int minPeriod = stream->minPeriod;
  int maxPeriod = stream->maxPeriod;
  int minDiff, maxDiff, retPeriod;
  int skip = computeSkip(stream, stream->sampleRate);
  int period;

  if (stream->numChannels == 1 && skip == 1) {
    period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &minDiff,
                                    &maxDiff);
  } else {
    downSampleInput(stream, samples, skip);
    period = findPitchPeriodInRange(stream->downSampleBuffer, minPeriod / skip,
                                    maxPeriod / skip, &minDiff, &maxDiff);
    if (skip != 1) {
      period *= skip;
      minPeriod = period - (skip << 2);
      maxPeriod = period + (skip << 2);
      if (minPeriod < stream->minPeriod) {
        minPeriod = stream->minPeriod;
      }
      if (maxPeriod > stream->maxPeriod) {
        maxPeriod = stream->maxPeriod;
      }
      if (stream->numChannels == 1) {
        period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &minDiff,
                                        &maxDiff);
      } else {
        downSampleInput(stream, samples, 1);
        period = findPitchPeriodInRange(stream->downSampleBuffer, minPeriod,
                                        maxPeriod, &minDiff, &maxDiff);
      }
    }
  }
  if (prevPeriodBetter(stream, minDiff, maxDiff, preferNewPeriod)) {
    retPeriod = stream->prevPeriod;
  } else {
    retPeriod = period;
  }
  stream->prevMinDiff = minDiff;
  stream->prevPeriod = period;
  return retPeriod;
}