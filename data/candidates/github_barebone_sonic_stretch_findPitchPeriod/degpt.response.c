int findPitchPeriod(sonicStream stream,short *samples,int preferNewPeriod)

{
  int iVar1;
  int period;
  int skip;
  int retPeriod;
  int maxDiff;
  int minDiff;
  int maxPeriod;
  int minPeriod;
  int preferNewPeriod_local;
  short *samples_local;
  sonicStream stream_local;
  
  minPeriod = stream->minPeriod;
  maxPeriod = stream->maxPeriod;
  preferNewPeriod_local = preferNewPeriod;
  samples_local = samples;
  stream_local = stream;
  iVar1 = computeSkip(stream,stream->sampleRate);
  if ((stream_local->numChannels == 1) && (iVar1 == 1)) {
    period = findPitchPeriodInRange(samples_local,minPeriod,maxPeriod,&minDiff,&maxDiff);
  }
  else {
    downSampleInput(stream_local,samples_local,iVar1);
    period = findPitchPeriodInRange
                       (stream_local->downSampleBuffer,minPeriod / iVar1,maxPeriod / iVar1,&minDiff,
                        &maxDiff);
    if (iVar1 != 1) {
      minPeriod = iVar1 * period + iVar1 * -4;
      maxPeriod = iVar1 * period + iVar1 * 4;
      if (minPeriod < stream_local->minPeriod) {
        minPeriod = stream_local->minPeriod;
      }
      if (stream_local->maxPeriod < maxPeriod) {
        maxPeriod = stream_local->maxPeriod;
      }
      if (stream_local->numChannels == 1) {
        period = findPitchPeriodInRange(samples_local,minPeriod,maxPeriod,&minDiff,&maxDiff);
      }
      else {
        downSampleInput(stream_local,samples_local,1);
        period = findPitchPeriodInRange
                           (stream_local->downSampleBuffer,minPeriod,maxPeriod,&minDiff,&maxDiff);
      }
    }
  }
  iVar1 = prevPeriodBetter(stream_local,minDiff,maxDiff,preferNewPeriod_local);
  if (iVar1 == 0) {
    retPeriod = period;
  }
  else {
    retPeriod = stream_local->prevPeriod;
  }
  stream_local->prevMinDiff = minDiff;
  stream_local->prevPeriod = period;
  return retPeriod;
}