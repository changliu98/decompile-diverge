void noise_est(float *state, float val, float inc, float dec, float min_val, float max_val) {
    if (val > *state + inc) {
        *state = *state + inc;
    } else if (val < *state - dec) {
        *state = *state - dec;
    } else {
        *state = val;
    }

    if (min_val > *state) {
        *state = min_val;
    }
    
    if (*state > max_val) {
        *state = max_val;
    }
}