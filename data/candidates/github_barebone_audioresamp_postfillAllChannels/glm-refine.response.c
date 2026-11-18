void __cdecl postfillAllChannels(Resample *cxt)
{
  int shift_amount = cxt->numSamples - cxt->numTaps;

  // If the remaining input samples are less than half the number of taps,
  // shift the buffers to retain the last `numTaps` samples.
  if ( cxt->numSamples - cxt->inputIndex < cxt->numTaps / 2 )
  {
    for (int c = 0; c < cxt->numChannels; ++c)
      memmove(cxt->buffers[c], &cxt->buffers[c][shift_amount], 4LL * cxt->numTaps);
    
    cxt->outputOffset -= (double)shift_amount;
    cxt->inputIndex -= shift_amount;
  }

  // Zero-fill the remainder of the buffers from the current input index.
  for (int c = 0; c < cxt->numChannels; ++c)
    memset(&cxt->buffers[c][cxt->inputIndex], 0, 4LL * (cxt->numSamples - cxt->inputIndex));
  
  cxt->flags |= 0x200u;
  cxt->inputIndex += cxt->numTaps / 2;
}