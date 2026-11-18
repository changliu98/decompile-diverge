int PITCH_DETECT_findPitchPeriod(PITCH_DETECT *pd, short *inbuf, int preferNewPeriod)
{
    int period;
    int retPeriod;
    int minDiff, maxDiff;
    int minPeriod = pd->minPeriod;
    int maxPeriod = pd->maxPeriod;
    int skip = computeSkip(pd, pd->sampleRate);
    if (pd->downSample == 1 && skip == 1) {
        period = findPitchPeriodInRange(inbuf, minPeriod, maxPeriod,
                                        &minDiff, &maxDiff);
    } else {
        downSampleInput(pd, inbuf, skip);
        period = findPitchPeriodInRange(pd->downSampBuffer,
                                        minPeriod/skip, maxPeriod/skip,
                                        &minDiff, &maxDiff);
        if (skip != 1) {

            period *= skip;
            minPeriod = period - (skip << 2);
            maxPeriod = period + (skip << 2);
            if (minPeriod < pd->minPeriod) minPeriod = pd->minPeriod;
            if (maxPeriod > pd->maxPeriod) maxPeriod = pd->maxPeriod;

            if (pd->downSample == 1) {
                period = findPitchPeriodInRange(inbuf, minPeriod, maxPeriod,
                                                &minDiff, &maxDiff);
            } else {
                downSampleInput(pd, inbuf, 1);
                period = findPitchPeriodInRange(pd->downSampBuffer,
                                                minPeriod, maxPeriod,
                                                &minDiff, &maxDiff);
            }
        }
    }

    if (prevPeriodBetter(pd, minDiff, maxDiff, preferNewPeriod)) {
        retPeriod = pd->lastPeriod;
    } else {
        retPeriod = period;
    }
    pd->lastMinDiff = minDiff;
    pd->lastPeriod = period;
    return retPeriod;
}