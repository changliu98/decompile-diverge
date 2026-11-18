int plot_digit_wierd(char c, float x, float y, float dx, float dy, float *out_x, float *out_y) {
    int count = 0;
    int ret_val = 0;
    float cur_x, cur_y;

    if (c < '0' || c > '9') {
        return 0;
    }

    int digit = c - '0';
    int end = lt[digit + 1];
    int limit = lt[digit + 2] - 1;

    for (int i = end; i <= limit; i++) {
        int row = lb[i] / 10;
        int col = lb[i] % 10;
        
        float offset_x = (float)row * dx;
        float offset_y = (float)col * dy;

        if (i != end) {
            out_x[count] = cur_x;
            out_y[count] = cur_y;
            count++;

            out_x[count] = x - offset_x;
            out_y[count] = y - offset_y;
            count++;
        }

        cur_x = x - offset_x;
        cur_y = y - offset_y;
    }

    ret_val = count;
    return ret_val;
}