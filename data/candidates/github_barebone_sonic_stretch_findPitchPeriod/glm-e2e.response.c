Main decompiled function
int findPitchPeriod(struct State *state, const short *samples, int usePrev) {
    int minPeriod = state->minPeriod;
    int maxPeriod = state->maxPeriod;
    int period = findPitchPeriodInRange(state, samples, state->prevPeriod, (int*)0, (int*)0);
    int minDiff;
    int maxDiff;
    int retPeriod;

    if (state->field_50 == 1 && period == 1) {
        retPeriod = findPitchPeriodInRange(state, samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
    } else {
        downSampleInput(state, samples, period);
        
        // Note: idivl instruction implies signed division
        retPeriod = findPitchPeriodInRange(state, (short*)state->field_18, minPeriod / period, maxPeriod / period, &minDiff, &maxDiff);
        
        if (period != 1) {
            retPeriod *= period;
            minPeriod = retPeriod - (period * 4);
            maxPeriod = retPeriod + (period * 4);
            
            if (minPeriod < state->minPeriod) {
                minPeriod = state->minPeriod;
            }
            if (maxPeriod > state->maxPeriod) {
                maxPeriod = state->maxPeriod;
            }
            
            if (state->field_50 == 1) {
                retPeriod = findPitchPeriodInRange(state, samples, minPeriod, maxPeriod, &minDiff, &maxDiff);
            } else {
                downSampleInput(state, samples, 1);
                retPeriod = findPitchPeriodInRange(state, (short*)state->field_18, minPeriod, maxPeriod, &minDiff, &maxDiff);
            }
        }
    }

    if (prevPeriodBetter(state, minDiff, maxDiff, usePrev)) {
        retPeriod = state->prevMinDiff;
    }

    state->prevMaxDiff = minDiff;
    state->prevMinDiff = retPeriod;
    
    return retPeriod;
}