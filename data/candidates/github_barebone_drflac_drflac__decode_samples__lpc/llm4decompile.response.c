drflac_bool32 drflac__decode_samples__lpc(drflac_bs *bs, drflac_uint32 blockSize, drflac_uint32 bitsPerSample, drflac_uint8 lpcOrder, drflac_int32 *pDecodedSamples)
{
    drflac_uint8 i;
    drflac_int32 coefficients[32];
    drflac_int8 lpcShift;
    drflac_uint8 lpcPrecision;


    for (i = 0; i < lpcOrder; ++i) {
        drflac_int32 sample;
        if (!drflac__read_int32(bs, bitsPerSample, &sample)) {
            return 0;
        }

        pDecodedSamples[i] = sample;
    }

    if (!drflac__read_uint8(bs, 4, &lpcPrecision)) {
        return 0;
    }

    if (lpcPrecision == 15) {
        return 0;
    }

    lpcPrecision += 1;

    if (!drflac__read_int8(bs, 5, &lpcShift)) {
        return 0;
    }

    if (lpcShift < 0) {
        return 0;
    }

    memset((coefficients), 0, (sizeof(coefficients)));
    for (i = 0; i < lpcOrder; ++i) {
        if (!drflac__read_int32(bs, lpcPrecision, coefficients + i)) {
            return 0;
        }
    }

    if (!drflac__decode_samples_with_residual(bs, bitsPerSample, blockSize, lpcOrder, lpcShift, lpcPrecision, coefficients, pDecodedSamples)) {
        return 0;
    }

    return 1;
}