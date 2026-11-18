int findPitchPeriod(sonicStream stream, short *samples, int numSamples) {
  int period, minPeriod, maxPeriod, bestCorr, skip, bestCorrQuality;
  minPeriod = stream->minPeriod;
  maxPeriod = stream->maxPeriod;
  skip = computeSkip(stream, stream->numChannels);
  if (stream->numChannels == 1 && skip == 1) {
    period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &bestCorr,
                                    &bestCorrQuality);
  } else {
    downSampleInput(stream, samples, skip);
    period = findPitchPeriodInRange(stream->downSampledInput, minPeriod / skip,
                                    maxPeriod / skip, &bestCorr,
                                    &bestCorrQuality);
    if (skip != 1) {
      minPeriod = period * skip - 4 * skip;
      maxPeriod = period * skip + 4 * skip;
      if (minPeriod < stream->minPeriod) minPeriod = stream->minPeriod;
      if (maxPeriod > stream->maxPeriod) maxPeriod = stream->maxPeriod;
      if (stream->numChannels == 1) {
        period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &bestCorr,
                                        &bestCorrQuality);
      } else {
        downSampleInput(stream, samples, 1);
        period = findPitchPeriodInRange(stream->downSampledInput, minPeriod,
                                        maxPeriod, &bestCorr, &bestCorrQuality);
      }
    }
  }
  int result;
  if (prevPeriodBetter(stream, bestCorr, bestCorrQuality, numSamples)) {
    result = stream->prevPeriod;
  } else {
    result = period;
  }
  stream->prevCorr = bestCorr;
  stream->prevPeriod = period;
  return result;
}