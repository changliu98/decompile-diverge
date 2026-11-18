int adjust_plines_for_skipcol(win_T *wp) {
    int plines = 0;
    
    if (wp->w_skipcol != 0) {
        int w_width = wp->w_width;
        int col_off = win_col_off(wp);
        int width = w_width - col_off;
        
        if (wp->w_skipcol >= width) {
            int diff = wp->w_skipcol - width;
            int col_off2 = win_col_off2(wp);
            plines = (diff / (diff + col_off2)) + 1;
        } else {
            plines = 0;
        }
    }
    
    return plines;
}