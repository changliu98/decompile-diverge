void drv_generic_graphic_window(int x, int w, int max_w, int *x_out, int *w_out) {
    int x_start = x;
    int x_end = x + w;

    *x_out = 0;
    *w_out = 0;

    if (x_start <= max_w && x_end >= 0 && w >= 1) {
        if (x_start < 0) {
            x_start = 0;
        }
        if (x_end > max_w) {
            x_end = max_w;
        }
        
        *x_out = x_start;
        *w_out = x_end - x_start;
    }
}