int _inverse_rot(struct params *in, struct out_params *out) {
    if (in->field4 == 0 || in->field8 == 0) {
        return 1;
    }
    
    out->field0 = 0;
    out->field4 = 0x100000 / in->field8;
    out->field8 = 0x100000 / in->field4;
    out->field12 = 0;
    out->field16 = (0 - (in->field20 * out->field8)) / 0x400;
    out->field20 = (0 - (in->field16 * out->field4)) / 0x400;
    
    return 0;
}