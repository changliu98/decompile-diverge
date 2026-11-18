static int drflac__decode_samples_with_lpc(drflac_bs* pBS, unsigned int blocksize, unsigned int bitsPerSample, unsigned char lpcOrder, drflac_int32* pDecodedSamples)
{
    drflac_int32 coefficients[32];
    unsigned char lpcPrecision;
    signed char lpcShift;
    unsigned char i;

    for (i = 0; i < lpcOrder; ++i) {
        drflac_int32 initialSample;
        if (!drflac__read_int32(pBS, bitsPerSample, &initialSample)) {
            return 0;
        }
        pDecodedSamples[i] = initialSample;
    }

    if (!drflac__read_uint8(pBS, 4, &lpcPrecision)) {
        return 0;
    }
    if (lpcPrecision == 15) {
        return 0;
    }
    ++lpcPrecision;

    if (!drflac__read_int8(pBS, 5, &lpcShift)) {
        return 0;
    }
    if (lpcShift < 0) {
        return 0;
    }

    memset((coefficients), 0, (sizeof(coefficients)));
    for (i = 0; i < lpcOrder; ++i) {
        if (!drflac__read_int32(pBS, lpcPrecision, &(coefficients[i]))) {
            return 0;
        }
    }

    if (!drflac__decode_samples_with_residual(pBS, bitsPerSample, blocksize, lpcOrder, lpcShift, lpcPrecision, coefficients, pDecodedSamples)) {
        return 0;
    }

    return 1;
}