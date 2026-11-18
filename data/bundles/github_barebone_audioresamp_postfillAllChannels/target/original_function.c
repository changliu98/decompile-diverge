static void postfillAllChannels (Resample *cxt)
{
    int c;

    if (cxt->numSamples - cxt->inputIndex < cxt->numTaps / 2) {
        for (c = 0; c < cxt->numChannels; ++c)
            memmove (cxt->buffers [c], cxt->buffers [c] + cxt->numSamples - cxt->numTaps, cxt->numTaps * sizeof (artsample_t));

        cxt->outputOffset -= cxt->numSamples - cxt->numTaps;
        cxt->inputIndex -= cxt->numSamples - cxt->numTaps;
    }

    for (c = 0; c < cxt->numChannels; ++c) {
        memset (cxt->buffers [c] + cxt->inputIndex, 0, (cxt->numSamples - cxt->inputIndex) * sizeof (artsample_t));
#ifdef ENABLE_EXTRAPOLATION
        if (cxt->flags & EXTRAPOLATE_ENDPOINTS)
            extrapolate_forward (cxt->buffers [c] + cxt->inputIndex - cxt->numTaps / 2, cxt->numTaps / 2, cxt->numTaps / 2);
#endif
    }

    cxt->flags |= RESAMPLER_FLUSHED;
    cxt->inputIndex += cxt->numTaps / 2;
}