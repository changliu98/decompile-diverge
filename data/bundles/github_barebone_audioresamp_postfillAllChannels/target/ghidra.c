void postfillAllChannels(Resample *cxt)

{
  int c;
  Resample *cxt_local;
  
  if (cxt->numSamples - cxt->inputIndex < cxt->numTaps / 2) {
    for (c = 0; c < cxt->numChannels; c = c + 1) {
      memmove(cxt->buffers[c],cxt->buffers[c] + ((long)cxt->numSamples - (long)cxt->numTaps),
              (long)cxt->numTaps << 2);
    }
    cxt->outputOffset = cxt->outputOffset - (double)(cxt->numSamples - cxt->numTaps);
    cxt->inputIndex = cxt->inputIndex - (cxt->numSamples - cxt->numTaps);
  }
  for (c = 0; c < cxt->numChannels; c = c + 1) {
    memset(cxt->buffers[c] + cxt->inputIndex,0,(long)(cxt->numSamples - cxt->inputIndex) << 2);
  }
  cxt->flags = cxt->flags | 0x200;
  cxt->inputIndex = cxt->numTaps / 2 + cxt->inputIndex;
  return;
}