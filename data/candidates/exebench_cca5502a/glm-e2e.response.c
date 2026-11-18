int modpars_to_struct(float *out_val, int *idx, int *max_idx, float *val, float *arr) {
    if (*idx == 1) {
        *out_val = *val;
        return 1;
    } else if (*idx > *max_idx) {
        *out_val = *val;
        *max_idx = *idx;
        arr[*idx - 2] = *val;
        return 1;
    } else if (*idx > 1) {
        *out_val = arr[*idx - 2];
        return 0;
    } else {
        return 0;
    }
}