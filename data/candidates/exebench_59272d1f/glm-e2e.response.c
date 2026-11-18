void bo_backoff(int *val, int max_val) {
    // Wait in a loop until *val becomes 0
    while (*val != 0) {
        (*val)--;
    }

    // Double the value, but cap it at max_val
    if (*val * 2 < max_val) {
        *val = *val * 2;
    } else {
        *val = max_val;
    }
}