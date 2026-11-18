void idctRows(int16_t *block) {
    for (int i = 0; i < 8; i++) {
        // Check if elements 1 to 7 are all zero
        if ((block[1] | block[2] | block[3] | block[4] | 
             block[5] | block[6] | block[7]) == 0) {
            // Fast path: DC-only row
            short val = block[0];
            for (int j = 1; j < 8; j++) {
                block[j] = val;
            }
        } else {
            // Full IDCT calculation
            short x5 = block[5];
            short x3 = block[3];
            short x6 = x5 - x3;
            short x4 = x5 + x3;
            
            short x1 = block[1];
            short x7 = block[7];
            short x0 = x1 + x7;
            short x2 = x1 - x7;
            
            short t1 = imul_b1_b3(x6 - x2);
            short t2 = imul_b2(x2) - t1;
            short t3 = imul_b1_b3(x6) - t1;
            
            short s0 = x0 - x4;
            short s1 = x0 + x4;
            
            short s2 = t2 - s1;
            short s3 = imul_b4(s0) - s2;
            short s4 = s3 + t3;
            
            short y0 = block[0];
            short y4 = block[4];
            short y1 = y0 + y4;
            short y2 = y0 - y4;
            
            short y3 = block[2];
            short y5 = block[6];
            short y6 = y3 - y5;
            short y7 = y3 + y5;
            
            short t4 = imul_b5(y6) - y7;
            
            short u1 = y1 + y7;
            short u2 = y1 - y7;
            short u3 = y2 + t4;
            short u4 = y2 - t4;
            
            // Store the computed results back into the block
            block[0] = u1 + s1;
            block[1] = u3 + s2;
            block[2] = u4 + s3;
            block[3] = u2 - s4;
            block[4] = u2 + s4;
            block[5] = u4 - s3;
            block[6] = u3 - s2;
            block[7] = u1 - s1;
        }
        
        // Advance to the next row (16 bytes)
        block += 8;
    }
}