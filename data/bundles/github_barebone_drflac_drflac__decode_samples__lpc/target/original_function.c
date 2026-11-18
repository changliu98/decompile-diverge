static drflac_bool32 drflac__decode_samples__lpc(drflac_bs* bs, drflac_uint32 blockSize, drflac_uint32 bitsPerSample, drflac_uint8 lpcOrder, drflac_int32* pDecodedSamples)
{
    drflac_uint8 i;
    drflac_uint8 lpcPrecision;
    drflac_int8 lpcShift;
    drflac_int32 coefficients[32];

    /* Warm up samples. */
    for (i = 0; i < lpcOrder; ++i) {
        drflac_int32 sample;
        if (!drflac__read_int32(bs, bitsPerSample, &sample)) {
            return DRFLAC_FALSE;
        }

        pDecodedSamples[i] = sample;
    }

    if (!drflac__read_uint8(bs, 4, &lpcPrecision)) {
        return DRFLAC_FALSE;
    }
    if (lpcPrecision == 15) {
        return DRFLAC_FALSE;    /* Invalid. */
    }
    lpcPrecision += 1;

    if (!drflac__read_int8(bs, 5, &lpcShift)) {
        return DRFLAC_FALSE;
    }

    /*
    From the FLAC specification:

        Quantized linear predictor coefficient shift needed in bits (NOTE: this number is signed two's-complement)

    Emphasis on the "signed two's-complement". In practice there does not seem to be any encoders nor decoders supporting negative shifts. For now dr_flac is
    not going to support negative shifts as I don't have any reference files. However, when a reference file comes through I will consider adding support.
    */
    if (lpcShift < 0) {
        return DRFLAC_FALSE;
    }

    DRFLAC_ZERO_MEMORY(coefficients, sizeof(coefficients));
    for (i = 0; i < lpcOrder; ++i) {
        if (!drflac__read_int32(bs, lpcPrecision, coefficients + i)) {
            return DRFLAC_FALSE;
        }
    }

    if (!drflac__decode_samples_with_residual(bs, bitsPerSample, blockSize, lpcOrder, lpcShift, lpcPrecision, coefficients, pDecodedSamples)) {
        return DRFLAC_FALSE;
    }

    return DRFLAC_TRUE;
}