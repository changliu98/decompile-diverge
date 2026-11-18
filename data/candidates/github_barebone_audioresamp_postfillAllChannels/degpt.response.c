void postfillAllChannels(Resample *context)
{
  int channelIndex;
  
  // Check if there are fewer samples remaining than half the filter length
  if (context->numSamples - context->inputIndex < context->numTaps / 2) {
    // Shift existing buffer data to the beginning for each channel
    for (channelIndex = 0; channelIndex < context->numChannels; channelIndex++) {
      memmove(context->buffers[channelIndex], context->buffers[channelIndex] + (context->numSamples - context->numTaps),
              (size_t)context->numTaps << 2);
    }
    // Adjust output offset and input index to reflect the shift
    context->outputOffset -= (double)(context->numSamples - context->numTaps);
    context->inputIndex -= (context->numSamples - context->numTaps);
  }
  // Zero-pad the remaining space in each channel's buffer
  for (channelIndex = 0; channelIndex < context->numChannels; channelIndex++) {
    memset(context->buffers[channelIndex] + context->inputIndex, 0, (size_t)(context->numSamples - context->inputIndex) << 2);
  }
  // Set the flag indicating that post-processing is complete
  context->flags |= 0x200;
  // Advance the input index by half the filter length
  context->inputIndex += context->numTaps / 2;
}