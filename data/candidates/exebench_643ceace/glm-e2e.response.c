void image_fit(int64_t src_w, int64_t src_h, int64_t dst_w, int64_t dst_h, int32_t *out_w, int32_t *out_h, int8_t fit) {
    float ratio_w = (float)src_w / (float)src_h;
    float ratio_h = (float)dst_w / (float)dst_h;

    if (fit < 1 || fit > 2) {
        if (ratio_h > ratio_w) {
            fit = 1;
        } else {
            fit = 2;
        }
    }

    if (fit == 1) {
        *out_h = (int32_t)((float)dst_w * ratio_w);
        *out_w = dst_w;
    } else {
        *out_w = (int32_t)((float)dst_h / ratio_w);
        *out_h = dst_h;
    }
}