int __cdecl findPitchPeriod(sonicStream stream, short *samples, int preferNewPeriod)
{
    int period;
    int retPeriod;
    int maxDiff;
    int minDiff;
    int maxPeriod;
    int minPeriod;
    int skip;

    minPeriod = stream->minPeriod;
    maxPeriod = stream->maxPeriod;
    skip = computeSkip(stream, stream->sampleRate);

    if (stream->numChannels == 1 && skip == 1) {
        // Mono audio with no downsampling: search directly on the original samples
        period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
    } else {
        // Multi-channel or skip > 1: downsample first to find an approximate pitch period
        downSampleInput(stream, samples, skip);
        period = findPitchPeriodInRange(stream->downSampleBuffer, minPeriod / skip, maxPeriod / skip, &minDiff, &maxDiff);

        if (skip != 1) {
            // Refine the pitch period around the approximation
            int approxPeriod = period * skip;
            minPeriod = approxPeriod - 4 * skip;
            maxPeriod = approxPeriod + 4 * skip;

            if (minPeriod < stream->minPeriod) {
                minPeriod = stream->minPeriod;
            }
            if (maxPeriod > stream->maxPeriod) {
                maxPeriod = stream->maxPeriod;
            }

            if (stream->numChannels == 1) {
                // Mono: search directly on the original samples within the refined range
                period = findPitchPeriodInRange(samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
            } else {
                // Multi-channel: downsample with skip=1 and search within the refined range
                downSampleInput(stream, samples, 1);
                period = findPitchPeriodInRange(stream->downSampleBuffer, minPeriod, maxPeriod, &minDiff, &maxDiff);
            }
        }
    }

    // Decide whether to use the previously found period or the newly found one
    if (prevPeriodBetter(stream, minDiff, maxDiff, preferNewPeriod)) {
        retPeriod = stream->prevPeriod;
    } else {
        retPeriod = period;
    }

    // Save state for the next call
    stream->prevMinDiff = minDiff;
    stream->prevPeriod = period;

    return retPeriod;
}