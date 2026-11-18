void __cdecl postfillAllChannels(Resample *cxt)
{
  int c; // [rsp+4h] [rbp-Ch]
  int ca; // [rsp+4h] [rbp-Ch]

  if ( cxt->numSamples - cxt->inputIndex < cxt->numTaps / 2 )
  {
    for ( c = 0; c < cxt->numChannels; ++c )
      memmove(cxt->buffers[c], &cxt->buffers[c][cxt->numSamples - cxt->numTaps], 4LL * cxt->numTaps);
    cxt->outputOffset = cxt->outputOffset - (double)(cxt->numSamples - cxt->numTaps);
    cxt->inputIndex -= cxt->numSamples - cxt->numTaps;
  }
  for ( ca = 0; ca < cxt->numChannels; ++ca )
    memset(&cxt->buffers[ca][cxt->inputIndex], 0, 4LL * (cxt->numSamples - cxt->inputIndex));
  cxt->flags |= 0x200u;
  cxt->inputIndex += cxt->numTaps / 2;
}