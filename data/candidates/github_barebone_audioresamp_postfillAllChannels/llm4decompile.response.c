void postfillAllChannels(Resample *cxt)
{
    int c;

    if (cxt->numSamples - cxt->inputIndex < cxt->numTaps / 2) {
        for (c = 0; c < cxt->numChannels; c++) {
            memmove(cxt->buffers[c], cxt->buffers[c] + cxt->numSamples - cxt->numTaps,
                    cxt->numTaps * sizeof(float));
        }
        cxt->outputOffset -= (double)(cxt->numSamples - cxt->numTaps);
        cxt->inputIndex -= (cxt->numSamples - cxt->numTaps);
    }
    for (c = 0; c < cxt->numChannels; c++) {
        memset(cxt->buffers[c] + cxt->inputIndex, 0,
               (cxt->numSamples - cxt->inputIndex) * sizeof(float));
    }
    cxt->inputIndex += cxt->numTaps / 2;
    cxt->flags |= 0x200;
}