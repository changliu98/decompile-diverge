static int mpeg3video_idctcol(short *samples)
{
    int i;
    int32_t a, b, c, d, e, f;
    int32_t x, y, z;
    int32_t last_x, last_y, last_z;
    int32_t last_a, last_b, last_c, last_d, last_e, last_f;
    int32_t last_samples[8];

    last_x = samples[0];
    last_y = samples[1];
    last_z = samples[2];
    last_a = samples[3];
    last_b = samples[4];
    last_c = samples[5];
    last_d = samples[6];
    last_e = samples[7];
    last_f = samples[8];

    for (i = 0;; i++) {
        if (last_a == 0 && last_b == 0 && last_c == 0 &&
            last_d == 0 && last_e == 0 && last_f == 0) {
            x = (last_x + 32) >> 6;
            y = (last_y + 32) >> 6;
            z = (last_z + 32) >> 6;
            a = x + y;
            b = y + z;
            c = z + x;
            d = x + y + z;
            e = a + b + c;
            f = b + c + d;
            last_a = a;
            last_b = b;
            last_c = c;
            last_d = d;
            last_e = e;
            last_f = f;
        }
        samples[0] = (int)(last_x + (last_a * 1108 + last_e * 799 + 4) >> 8);
        samples[1] = (int)(last_y + (last_b * 1108 + last_f * 799 + 4) >> 8);
        samples[2] = (int)(last_z + (last_c