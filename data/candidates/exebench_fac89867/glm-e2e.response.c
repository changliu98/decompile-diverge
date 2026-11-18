void ne_post_filter16_double(double *out, const double *in, const struct FilterParams *params) {
    double diff0  = in[0]  - in[15];
    double diff1  = in[1]  - in[14];
    double diff2  = in[2]  - in[13];
    double diff3  = in[3]  - in[12];
    double diff4  = in[4]  - in[11];
    double diff5  = in[5]  - in[10];
    double diff6  = in[6]  - in[9];
    double diff7  = in[7]  - in[8];

    double adj0 = in[7]  - diff7 / 2.0;
    double adj1 = in[6]  - diff6 / 2.0;
    double adj2 = in[5]  - diff5 / 2.0;
    double adj3 = in[4]  - diff4 / 2.0;
    double adj4 = in[3]  - diff3 / 2.0;
    double adj5 = in[2]  - diff2 / 2.0;
    double adj6 = in[1]  - diff1 / 2.0;
    double adj7 = in[0]  - diff0 / 2.0;

    // Intermediate scaling and adjustments
    diff7 = diff7 - (diff6 * params->scale_3c) / 3.0;
    diff6 = diff6 - (diff7 * params->scale_20) / 3.0;
    diff6 = diff6 - (diff5 * params->scale_40) / 3.0;
    diff5 = diff5 - (diff6 * params->scale_24) / 3.0;
    diff5 = diff5 - (diff4 * params->scale_44) / 3.0;
    diff4 = diff4 - (diff5 * params->scale_28) / 3.0;
    diff4 = diff4 - (diff3 * params->scale_48) / 3.0;
    diff3 = diff3 - (diff4 * params->scale_2c) / 3.0;
    diff3 = diff3 - (diff2 * params->scale_4c) / 3.0;
    diff2 = diff2 - (diff3 * params->scale_30) / 3.0;
    diff2 = diff2 - (diff1 * params->scale_50) / 3.0;
    diff1 = diff1 - (diff2 * params->scale_34) / 3.0;
    diff1 = diff1 - (diff0 * params->scale_54) / 3.0;
    diff0 = diff0 - (diff1 * params->scale_38) / 3.0;

    // Final scaling
    diff0 = (diff0 * 3.0) / params->scale_1c;
    diff1 = (diff1 * 3.0) / params->scale_18;
    diff2 = (diff2 * 3.0) / params->scale_14;
    diff3 = (diff3 * 3.0) / params->scale_10;
    diff4 = (diff4 * 3.0) / params->scale_c;
    diff5 = (diff5 * 3.0) / params->scale_8;
    diff6 = (diff6 * 3.0) / params->scale_4;
    diff7 = (diff7 * 3.0) / params->scale_0;

    // Output assignments
    out[0]  = adj7 + diff0 / 2.0;
    out[1]  = adj6 + diff1 / 2.0;
    out[2]  = adj5 + diff2 / 2.0;
    out[3]  = adj4 + diff3 / 2.0;
    out[4]  = adj3 + diff4 / 2.0;
    out[5]  = adj2 + diff5 / 2.0;
    out[6]  = adj1 + diff6 / 2.0;
    out[7]  = adj0 + diff7 / 2.0;

    out[8]  = adj0 - diff7;
    out[9]  = adj1 - diff6;
    out[10] = adj2 - diff5;
    out[11] = adj3 - diff4;
    out[12] = adj4 - diff3;
    out[13] = adj5 - diff2;
    out[14] = adj6 - diff1;
    out[15] = adj7 - diff0;
}