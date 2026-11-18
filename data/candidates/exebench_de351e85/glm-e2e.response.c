void P_stats(float *data, int *count, int *start_idx, int *end_idx, float *max_val, int *max_idx, int *flags) {
    int current_run = 0;
    *count = 0;
    *max_idx = 0;
    *max_val = 0.0f;
    *start_idx = 0;
    *end_idx = 0;

    // First loop: find the maximum value and its index among positive numbers
    for (int i = 0; i < 24; i++) {
        if (data[i] > 0.0f) {
            (*count)++;
            if (data[i] > *max_val) {
                *max_val = data[i];
                *max_idx = i;
            }
        }
    }

    // Second loop: find the longest contiguous run of positive numbers
    for (int i = 0; i < 24; i++) {
        flags[i] = 0;
        if (data[i] > 0.0f) {
            current_run++;
            flags[i] = 1;
        } else {
            if (current_run > *start_idx) {
                *start_idx = current_run;
                *end_idx = i - current_run;
            }
            current_run = 0;
        }
    }

    // Final check in case the longest run extends to the end of the array
    if (current_run > *start_idx) {
        *start_idx = current_run;
        *end_idx = 24 - current_run;
    }
}