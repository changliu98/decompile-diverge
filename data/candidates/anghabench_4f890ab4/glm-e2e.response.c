int ff_norm_qscale(int qscale, int type) {
    int result;

    // The switch evaluates (type - 0x80) and handles cases 0 to 3.
    // If it's outside this range (ja > 3), it falls through to the default case.
    switch (type - 0x80) {
        case 0:
            result = qscale;
            break;
        case 1:
            result = qscale >> 1;
            break;
        case 2:
            result = qscale >> 2;
            break;
        case 3:
            result = (0x3f - qscale + 2) >> 2;
            break;
        default:
            result = qscale;
            break;
    }
    
    return result;
}