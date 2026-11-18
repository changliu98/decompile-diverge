void quicktake_100_load_raw() {
    unsigned char buffer[0x4c190];
    int pred;
    int i;
    int row, col;
    int r, c;
    int diff;
    int gstep_idx;
    int rstep_idx;
    int avg;
    const short *rstep_ptr;

    pred = 0;
    getbithuff(-1, 0);
    memset(buffer, 0x80, 0x4c190);

    // Phase 1: Top two rows
    for (row = 2; row < height + 2; row++) {
        for (col = (row & 1) + 2; col < width + 2; col += 2) {
            diff = (buffer[(row - 1) * 0x284 + (col - 1)] + 
                    2 * buffer[(row - 1) * 0x284 + (col + 1)] + 
                    buffer[(row - 1) * 0x284 + (col - 2)]) >> 2;
            pred = diff + quicktake_100_load_raw_gstep[getbithuff(4, 0)];
            if (pred > 0xff) pred = 0xff;
            if (pred < 0) pred = 0;
            buffer[row * 0x284 + col] = pred;
            if (col < 4) {
                buffer[(row + 1) * 0x284 + ((~row) & 1)] = pred;
                buffer[row * 0x284 + (col - 2)] = pred;
            }
            if (row == 2) {
                buffer[(row - 1) * 0x284 + (col + 3)] = pred;
                buffer[(row - 1) * 0x284 + (col + 1)] = pred;
            }
        }
    }

    // Phase 2: Main grid decoding
    for (i = 0; i < 2; i++) {
        for (row = 2 + i; row < height + 2; row += 2) {
            for (col = 3 - (row & 1); col < width + 2; col += 2) {
                if (row < 4 || col < 4) {
                    rstep_idx = 2;
                } else {
                    diff = buffer[(row - 2) * 0x284 + col] - buffer[(row - 2) * 0x284 + (col - 2)];
                    diff += (diff < 0) ? -1 : 0; // Equivalent to abs(diff) - 1
                    diff += buffer[row * 0x284 + (col - 2)] - buffer[(row - 2) * 0x284 + (col - 2)];
                    diff += (diff < 0) ? -1 : 0; // Equivalent to abs(diff) - 1
                    
                    if (diff < 4) {
                        rstep_idx = 0;
                    } else if (diff < 8) {
                        rstep_idx = 1;
                    } else if (diff < 16) {
                        rstep_idx = 2;
                    } else if (diff < 32) {
                        rstep_idx = 3;
                    } else {
                        rstep_idx = (diff < 48) ? 4 : 5;
                    }
                }
                
                avg = (buffer[(row - 2) * 0x284 + col] + buffer[row * 0x284 + (col - 2)]) >> 1;
                rstep_ptr = quicktake_100_load_raw_rstep[rstep_idx];
                pred = avg + rstep_ptr[getbithuff(2, 0)];
                if (pred > 0xff) pred = 0xff;
                if (pred < 0) pred = 0;
                buffer[row * 0x284 + col] = pred;
                
                if (row < 4) buffer[(row - 2) * 0x284 + (col + 2)] = pred;
                if (col < 4) buffer[(row + 2) * 0x284 + (col - 2)] = pred;
            }
        }
    }

    // Phase 3: Interpolation / Fill remaining
    for (row = 2; row < height + 2; row++) {
        for (col = 3 - (row & 1); col < width + 2; col += 2) {
            pred = (buffer[row * 0x284 + (col - 1)] + 
                    4 * buffer[row * 0x284 + col] + 
                    buffer[row * 0x284 + (col + 1)]) >> 1;
            pred -= 0x100;
            if (pred > 0xff) pred = 0xff;
            if (pred < 0) pred = 0;
            buffer[row * 0x284 + col] = pred;
        }
    }

    // Phase 4: Map to output
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            raw_image[row * raw_width + col] = quicktake_100_load_raw_t_curve[buffer[(row + 2) * 0x284 + (col + 2)]];
        }
    }

    maximum = 0x3ff;
}