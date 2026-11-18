void split(int start, int end, int *start_out, int *mid_out, int *end_out, int total) {
    int chunk_size = end - start + 1;
    if (chunk_size > 0) {
        int split_size = total / chunk_size;
        
        *start_out = start;
        *mid_out = start + split_size - 1;
        *end_out = start + split_size;
        *mid_out = end; // Note: see explanation below
    }
}