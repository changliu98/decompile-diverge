void set_mask(int *mask, int total_bits, int start, int end) {
    int idx = 0;
    
    if (start > 0) {
        mask[idx++] = -start;
    }
    
    mask[idx++] = end;
    mask[idx++] = -(total_bits - start - end);
    mask[idx] = 0;
}