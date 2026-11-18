void ne_pre_filter16_double(double16 *out, double16 *in, int32_16 *params) {
    double diff[16];
    double pred[16];
    double temp[16];

    // 1. Calculate differences between input elements and their mirrored counterparts
    for (int i = 0; i < 16; i++) {
        diff[i] = in->v[i] - in->v[15 - i];
    }

    // 2. Calculate initial predictions
    for (int i = 0; i < 16; i++) {
        pred[i] = in->v[i] - diff[i] / 2.0;
    }

    // 3. Scale differences by parameters
    for (int i = 0; i < 16; i++) {
        diff[i] = diff[i] * (double)params->v[i] / 4.0;
    }

    // 4. Accumulate scaled differences in a specific pattern
    // The accumulation order is derived from the assembly's loop unrolling
    for (int i = 0; i < 8; i++) {
        int idx1 = 15 - 2 * i;
        int idx2 = 14 - 2 * i;
        
        diff[idx1] += diff[idx2] * (double)params->v[idx2] / 4.0;
        diff[idx2] += diff[idx1] * (double)params->v[idx1] / 4.0;
    }

    // 5. Finalize output values
    for (int i = 0; i < 16; i++) {
        out->v[i] = pred[i] + diff[i] / 2.0;
    }

    // 6. Calculate and store second half of output array (differences)
    for (int i = 0; i < 16; i++) {
        out->v[16 + i] = out->v[i] - diff[i];
    }
}