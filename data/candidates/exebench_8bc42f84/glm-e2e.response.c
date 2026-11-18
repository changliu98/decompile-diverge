void mpeg3video_calc_mv(int *mv, int full_pel, int motion_code, int motion_residual, int is_vertical) {
    int range = 16 << full_pel;
    int delta;
    
    if (is_vertical != 0) {
        delta = *mv / 2;
    } else {
        delta = *mv;
    }
    
    if (motion_code > 0) {
        delta += ((motion_code - 1) << full_pel) + motion_residual + 1;
        if (delta < range) {
            // Do nothing
        } else {
            delta -= range * 2;
        }
    } else if (motion_code < 0) {
        delta -= ((-motion_code - 1) << full_pel) + motion_residual + 1;
        if (delta >= -range) {
            // Do nothing
        } else {
            delta += range * 2;
        }
    }
    
    if (is_vertical != 0) {
        *mv = delta * 2;
    } else {
        *mv = delta;
    }
}