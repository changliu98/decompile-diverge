void quant_u_dec(int quant_idx, float *val, float min_val, float max_val, int num_vals) {
    float step = (max_val - min_val) / (float)(num_vals - 1);
    *val = (float)quant_idx * step + min_val;
}