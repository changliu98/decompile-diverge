void vp8_short_inv_walsh4x4_simd(short *input, short *output) {
    short temp[16];
    int i;

    // First pass: Horizontal 1D Walsh-Hadamard Transform
    for (i = 0; i < 4; i++) {
        int a = input[0];
        int d = input[3];
        int b = input[1];
        int c = input[2];

        int sum_ad = a + d;
        int sum_bc = b + c;
        int diff_bc = b - c;
        int diff_ad = a - d;

        temp[0] = sum_ad + sum_bc;
        temp[1] = diff_bc + diff_ad;
        temp[2] = sum_ad - sum_bc;
        temp[3] = diff_ad - diff_bc;

        input += 1;
        temp += 1;
    }
    temp -= 4; // Reset temp pointer back to the start of the array

    // Second pass: Vertical 1D Walsh-Hadamard Transform
    for (i = 0; i < 4; i++) {
        int a = temp[0];
        int d = temp[3];
        int b = temp[1];
        int c = temp[2];

        int sum_ad = a + d;
        int sum_bc = b + c;
        int diff_bc = b - c;
        int diff_ad = a - d;

        int out0 = sum_ad + sum_bc;
        int out1 = diff_bc + diff_ad;
        int out2 = sum_ad - sum_bc;
        int out3 = diff_ad - diff_bc;

        temp[0] = (out0 + 3) >> 3;
        temp[1] = (out1 + 3) >> 3;
        temp[2] = (out2 + 3) >> 3;
        temp[3] = (out3 + 3) >> 3;

        temp += 4;
    }
    temp -= 16; // Reset temp pointer back to the start of the array

    // Final pass: Copy and interleave to the output block
    for (i = 0; i < 16; i++) {
        output[i * 8] = temp[i];
    }
}