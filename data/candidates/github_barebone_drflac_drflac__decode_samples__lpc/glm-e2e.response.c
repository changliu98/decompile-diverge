int drflac__decode_samples__lpc(drflac *p, int unused1, int unused2, uint8_t lpcOrder, int32_t *samplesOut) {
    int32_t prediction[32];
    int32_t temp;
    uint8_t order;
    int8_t lpcPrecision;
    uint8_t i;
    int result;

    // Read warm-up samples
    for (i = 0; i < lpcOrder; ++i) {
        if (!drflac__read_int32(p, 0, &temp)) {
            return 0;
        }
        samplesOut[i] = temp;
    }

    // Read LPC order
    if (!drflac__read_int8(p, 4, (int8_t *)&order)) {
        return 0;
    }

    // Check for invalid order
    if (order == 0x0F) {
        return 0;
    }
    order++;

    // Read LPC precision
    if (!drflac__read_int8(p, 5, &lpcPrecision)) {
        return 0;
    }

    // Check for invalid precision
    if (lpcPrecision < 0) {
        return 0;
    }

    // Read LPC coefficients
    memset(prediction, 0, sizeof(prediction));
    for (i = 0; i < lpcOrder; ++i) {
        if (!drflac__read_int32(p, order, &prediction[i])) {
            return 0;
        }
    }

    // Decode samples with residual
    if (!drflac__decode_samples_with_residual(p, unused2, unused1, lpcOrder, lpcPrecision, order, prediction, samplesOut)) {
        return 0;
    }

    return 1;
}