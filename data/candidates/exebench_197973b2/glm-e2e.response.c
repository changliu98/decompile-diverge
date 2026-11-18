void computesizes(int32_t *sizes, int total_size, int *max_size, int *out_size) {
    int current_sum = sizes[0];
    int best_sum = current_sum;
    int best_idx = (current_sum == 0) ? -1 : 0;
    int i = 1;

    while (1) {
        int valid = 0;
        if (current_sum >= *max_size) {
            valid = 1;
        } else if (*max_size >= (1 << (i - 1))) {
            valid = 1;
        }

        if (!valid) {
            break;
        }

        if (sizes[i] > 0) {
            current_sum += sizes[i];
            if (current_sum >= (1 << (i - 1))) {
                best_idx = i;
                best_sum = current_sum;
            }
        }
        i++;
    }

    *out_size = total_size - best_sum;

    if (best_idx == -1) {
        *max_size = 0;
    } else {
        *max_size = 1 << best_idx;
    }
}