void helper_float_19_recursive(float *data, int n) {
    if (n == 13) {
        // Base case: 8192-point FFT (2^13)
        // The loops are unrolled and vectorized in the original assembly.
        
        // Stage 1: 8-point FFTs
        for (int i = 0; i < 8192; i += 64) {
            for (int j = 0; j < 8; j++) {
                int idx = i + j;
                fft_butterfly_8(&data[idx], &data[idx + 8], &data[idx + 16], &data[idx + 24],
                                &data[idx + 32], &data[idx + 40], &data[idx + 48], &data[idx + 56]);
            }
        }

        // Stage 2: 64-point FFTs
        for (int i = 0; i < 8192; i += 512) {
            for (int j = 0; j < 64; j++) {
                int idx = i + j;
                fft_butterfly_8(&data[idx], &data[idx + 64], &data[idx + 128], &data[idx + 192],
                                &data[idx + 256], &data[idx + 320], &data[idx + 384], &data[idx + 448]);
            }
        }

        // Stage 3: 512-point FFTs
        for (int i = 0; i < 8192; i += 4096) {
            for (int j = 0; j < 512; j++) {
                int idx = i + j;
                fft_butterfly_8(&data[idx], &data[idx + 512], &data[idx + 1024], &data[idx + 1536],
                                &data[idx + 2048], &data[idx + 2560], &data[idx + 3072], &data[idx + 3584]);
            }
        }

        // Stage 4: 4096-point FFTs
        for (int i = 0; i < 8192; i += 8192) {
            for (int j = 0; j < 1024; j++) {
                int idx = i + j;
                // 2-point butterfly
                float a = data[idx];
                float b = data[idx + 4096];
                data[idx] = a + b;
                data[idx + 4096] = a - b;
            }
        }
    } else if (n == 16) {
        // Recursive case: 65536-point FFT (2^16)
        // Split into 8 sub-problems of size 2^13
        helper_float_19_recursive(data, 13);
        helper_float_19_recursive(data + 8192, 13);
        helper_float_19_recursive(data + 16384, 13);
        helper_float_19_recursive(data + 24576, 13);
        helper_float_19_recursive(data + 32768, 13);
        helper_float_19_recursive(data + 40960, 13);
        helper_float_19_recursive(data + 49152, 13);
        helper_float_19_recursive(data + 57344, 13);

        // Combine stage
        for (int i = 0; i < 65536; i += 16384) {
            for (int j = 0; j < 2048; j++) {
                int idx = i + j;
                fft_butterfly_8(&data[idx], &data[idx + 2048], &data[idx + 4096], &data[idx + 6144],
                                &data[idx + 8192], &data[idx + 10240], &data[idx + 12288], &data[idx + 14336]);
            }
        }
    } else if (n == 19) {
        // Recursive case: 524288-point FFT (2^19)
        // Split into 8 sub-problems of size 2^16
        helper_float_19_recursive(data, 16);
        helper_float_19_recursive(data + 65536, 16);
        helper_float_19_recursive(data + 131072, 16);
        helper_float_19_recursive(data + 196608, 16);
        helper_float_19_recursive(data + 262144, 16);
        helper_float_19_recursive(data + 327680, 16);
        helper_float_19_recursive(data + 393216, 16);
        helper_float_19_recursive(data + 458752, 16);

        // Combine stage
        for (int i = 0; i < 524288; i += 262144) {
            for (int j = 0; j < 16384; j++) {
                int idx = i + j;
                fft_butterfly_8(&data[idx], &data[idx + 16384], &data[idx + 32768], &data[idx + 49152],
                                &data[idx + 65536], &data[idx + 81920], &data[idx + 98304], &data[idx + 114688]);
            }
        }
    }
}