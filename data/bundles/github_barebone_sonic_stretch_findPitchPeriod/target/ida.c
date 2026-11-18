int __cdecl findPitchPeriod(sonicStream stream, short *samples, int preferNewPeriod)
{
  int period; // [rsp+0h] [rbp-30h]
  int perioda; // [rsp+0h] [rbp-30h]
  int skip; // [rsp+4h] [rbp-2Ch]
  int retPeriod; // [rsp+8h] [rbp-28h]
  int maxDiff; // [rsp+Ch] [rbp-24h] BYREF
  int minDiff; // [rsp+10h] [rbp-20h] BYREF
  int maxPeriod; // [rsp+14h] [rbp-1Ch]
  int minPeriod; // [rsp+18h] [rbp-18h]
  int preferNewPerioda; // [rsp+1Ch] [rbp-14h]
  short *samplesa; // [rsp+20h] [rbp-10h]
  sonicStream streama; // [rsp+28h] [rbp-8h]

  streama = stream;
  samplesa = samples;
  preferNewPerioda = preferNewPeriod;
  minPeriod = stream->minPeriod;
  maxPeriod = stream->maxPeriod;
  skip = computeSkip(stream, stream->sampleRate);
  if ( stream->numChannels == 1 && skip == 1 )
  {
LABEL_3:
    period = findPitchPeriodInRange(samplesa, minPeriod, maxPeriod, &minDiff, &maxDiff);
    goto LABEL_11;
  }
  downSampleInput(streama, samplesa, skip);
  period = findPitchPeriodInRange(streama->downSampleBuffer, minPeriod / skip, maxPeriod / skip, &minDiff, &maxDiff);
  if ( skip != 1 )
  {
    perioda = period * skip;
    minPeriod = perioda - 4 * skip;
    maxPeriod = 4 * skip + perioda;
    if ( minPeriod < streama->minPeriod )
      minPeriod = streama->minPeriod;
    if ( maxPeriod > streama->maxPeriod )
      maxPeriod = streama->maxPeriod;
    if ( streama->numChannels == 1 )
      goto LABEL_3;
    downSampleInput(streama, samplesa, 1);
    period = findPitchPeriodInRange(streama->downSampleBuffer, minPeriod, maxPeriod, &minDiff, &maxDiff);
  }
LABEL_11:
  if ( prevPeriodBetter(streama, minDiff, maxDiff, preferNewPerioda) )
    retPeriod = streama->prevPeriod;
  else
    retPeriod = period;
  streama->prevMinDiff = minDiff;
  streama->prevPeriod = period;
  return retPeriod;
}