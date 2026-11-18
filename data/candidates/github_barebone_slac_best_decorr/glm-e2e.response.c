int best_decorr(int arg1, int arg2, int arg3) {
    int best_bits = magnitude_bits(arg1, arg2, arg3);
    int best_idx = 0;
    int idx = 0;

    while (idx < 6) {
        int bits = decorrelate(arg1, arg2, arg3);
        idx++;
        
        if (bits < best_bits) {
            best_idx = idx;
            best_bits = bits;
        } else {
            bits = correlate(arg1, arg2, arg3);
            idx--;
            break;
        }
    }

    if (idx == 0) {
        int bits = correlate(arg1, arg2, arg3);
        idx--;
        
        if (bits < best_bits) {
            best_idx = idx;
            best_bits = bits;
        } else {
            decorrelate(arg1, arg2, arg3);
            idx++;
        }
    }

    return best_idx;
}