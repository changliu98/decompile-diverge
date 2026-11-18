void fht16(float *data) {
    // Stage 1: 16 size-2 FHTs
    for (int i = 0; i < 16; i += 4) {
        float a = data[i];
        float b = data[i + 1];
        float c = data[i + 2];
        float d = data[i + 3];

        float s1 = a + b;
        float s2 = a - b;
        float s3 = c + d;
        float s4 = c - d;

        data[i]     = s1 + s3;
        data[i + 2] = s1 - s3;
        data[i + 1] = s2 + s4;
        data[i + 3] = s2 - s4;
    }

    // Stage 2: 4 size-4 FHTs
    for (int i = 0; i < 16; i += 8) {
        float a = data[i];
        float b = data[i + 2];
        float c = data[i + 1];
        float d = data[i + 3];

        data[i]     = a + b;
        data[i + 2] = a - b;
        data[i + 1] = c + d;
        data[i + 3] = c - d;

        float e = data[i + 4];
        float f = data[i + 6];
        float g = data[i + 5];
        float h = data[i + 7];

        data[i + 4] = e + f;
        data[i + 6] = e - f;
        data[i + 5] = g + h;
        data[i + 7] = g - h;
    }

    // Stage 3: 2 size-8 FHTs
    for (int i = 0; i < 16; i += 8) {
        float a = data[i];
        float b = data[i + 4];
        float c = data[i + 2];
        float d = data[i + 6];

        data[i]     = a + b;
        data[i + 4] = a - b;
        data[i + 2] = c + d;
        data[i + 6] = c - d;

        float e = data[i + 1];
        float f = data[i + 5];
        float g = data[i + 3];
        float h = data[i + 7];

        float cos_pi_4 = 0.70710678118654752440f; // M_SQRT1_2

        float t1 = (f + h) * cos_pi_4;
        float t2 = (f - h) * cos_pi_4;

        data[i + 1] = e + t1;
        data[i + 5] = e - t1;
        data[i + 3] = g + t2;
        data[i + 7] = g - t2;
    }

    // Stage 4: 1 size-16 FHT
    {
        float a = data[0];
        float b = data[8];
        float c = data[4];
        float d = data[12];

        data[0]  = a + b;
        data[8]  = a - b;
        data[4]  = c + d;
        data[12] = c - d;

        float e = data[2];
        float f = data[10];
        float g = data[6];
        float h = data[14];

        float cos_pi_8 = 0.92387953251128675613f;
        float sin_pi_8 = 0.38268343236508977173f;

        float t1 = f * cos_pi_8 + h * sin_pi_8;
        float t2 = f * sin_pi_8 - h * cos_pi_8;

        data[2]  = e + t1;
        data[10] = e - t1;
        data[6]  = g + t2;
        data[14] = g - t2;

        float i_ = data[1];
        float j = data[9];
        float k = data[5];
        float l = data[13];

        float cos_3pi_8 = 0.38268343236508977173f;
        float sin_3pi_8 = 0.92387953251128675613f;

        float t3 = j * cos_3pi_8 + l * sin_3pi_8;
        float t4 = j * sin_3pi_8 - l * cos_3pi_8;

        data[1]  = i_ + t3;
        data[9]  = i_ - t3;
        data[5]  = k + t4;
        data[13] = k - t4;

        float m = data[3];
        float n = data[11];
        float o = data[7];
        float p = data[15];

        float t5 = n * cos_3pi_8 + p * sin_3pi_8;
        float t6 = n * sin_3pi_8 - p * cos_3pi_8;

        data[3]  = m + t5;
        data[11] = m - t5;
        data[7]  = o + t6;
        data[15] = o - t6;
    }
}