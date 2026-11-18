void quant_u(float *val, int *bin, float min, float max, int n) {
    float step = (max - min) / (n - 1);
    float boundary = min + step * 0.5;
    int i = 0;

    while (i < n - 1) {
        if (*val <= boundary) {
            break;
        }
        boundary += step;
        i++;
    }

    *val = min + i * step;
    *bin = i;
}