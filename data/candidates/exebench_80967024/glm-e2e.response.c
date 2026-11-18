void upcoef_len_cal(int len, int filter_len, int levels, int *out_len1, int *out_len2) {
    *out_len1 = len;
    *out_len2 = len;

    for (int i = 0; i < levels; i++) {
        *out_len2 = (*out_len2 * 2) + filter_len - 1;
        *out_len1 = (*out_len1 * 2) + filter_len - 2;
    }
}