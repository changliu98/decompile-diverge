void GetLims(double *arr, double max_val, double min_val, int n, int *lower, int *upper) {
    int found_lower = 0;
    int found_upper = 0;

    if (n == 0) {
        *lower = 0;
        *upper = -1;
        return;
    }

    for (int i = 0; i < n; i++) {
        double val = arr[i];
        
        if (val >= min_val && !found_lower) {
            *lower = 0;
            *upper = -1;
            found_lower = 1;
            found_upper = 1;
        } else {
            if (val >= max_val && !found_lower) {
                *lower = i;
                found_lower = 1;
            } else if (val >= min_val && !found_upper) {
                *upper = i - 1;
                found_upper = 1;
            }
        }
    }

    if (!found_lower) {
        *lower = 0;
        *upper = -1;
    } else if (!found_upper) {
        *upper = n - 1;
    }
}