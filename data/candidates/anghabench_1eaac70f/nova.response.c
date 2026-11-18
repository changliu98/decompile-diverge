static int unconv_uid(int val) {
    int ret;

    if (val >= 0) {
        ret = (val * ADC_RESOLUTION) + ADC_MIN_VALUE;
    } else {
        ret = -1; 
    }

    return ret;
}