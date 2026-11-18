void ne_post_filter8_double(double *out, const double *in, const Coefficients *params) {
    // Initial differences between symmetric elements of the input array
    double diff0 = in[0] - in[7];
    double diff1 = in[1] - in[6];
    double diff2 = in[2] - in[5];
    double diff3 = in[3] - in[4];

    // Intermediate calculations (subtracting half of the differences)
    double res3 = in[3] - (diff3 / 2.0);
    double res2 = in[2] - (diff2 / 2.0);
    double res1 = in[1] - (diff1 / 2.0);
    double res0 = in[0] - (diff0 / 2.0);

    // First pass of filtering using coefficients
    diff3 = diff3 - (diff2 * (double)params->coef7 / 8.0);
    diff2 = diff2 - (diff3 * (double)params->coef4 / 8.0);
    diff2 = diff2 - (diff1 * (double)params->coef6 / 8.0);
    diff1 = diff1 - (diff2 * (double)params->coef3 / 8.0);
    diff1 = diff1 - (diff0 * (double)params->coef5 / 8.0);
    diff0 = diff0 - (diff1 * (double)params->coef2 / 8.0);

    // Second pass of filtering and scaling
    diff0 = (diff0 * 8.0) / (double)params->coef1;
    diff1 = (diff1 * 8.0) / (double)params->coef0;
    diff2 = (diff2 * 8.0) / (double)params->coef7;
    diff3 = (diff3 * 8.0) / (double)params->coef6;

    // Final accumulation and output assignment
    out[0] = res0 + diff0 / 2.0;
    out[1] = res1 + diff1 / 2.0;
    out[2] = res2 + diff2 / 2.0;
    out[3] = res3 + diff3 / 2.0;
    
    // The second half of the output array mirrors the first half based on the differences
    out[4] = res3 - diff3;
    out[5] = res2 - diff2;
    out[6] = res1 - diff1;
    out[7] = res0 - diff0;
}