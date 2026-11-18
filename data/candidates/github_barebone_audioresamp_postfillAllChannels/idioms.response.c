static void postfillAllChannels(struct Resample *resample)
{
   int i;
   if (resample->numSamples - resample->inputIndex < resample->numTaps / 2)
   {
      for (i = 0; i < resample->numChannels; i++)
         memmove(resample->buffers[i], resample->buffers[i] + (resample->numSamples - resample->numTaps), resample->numTaps * sizeof(float));
      resample->outputOffset -= (resample->numSamples - resample->numTaps);
      resample->inputIndex -= (resample->numSamples - resample->numTaps);
   }
   for (i = 0; i < resample->numChannels; i++)
      memset(&resample->buffers[i][resample->inputIndex], 0, (resample->numSamples - resample->inputIndex) * sizeof(float));
   resample->flags |= 0x200;
   resample->inputIndex += resample->numTaps / 2;
}