int drflac__seek_subframe(drflac *pFlac, drflac_frame *pFrame, int channelIndex) {
    if (pFlac == NULL) {
        drflac_assert(0, "", 0x1547, "");
    }
    if (pFrame == NULL) {
        drflac_assert(0, "", 0x1548, "");
    }

    drflac_subframe *pSubframe = (drflac_subframe *)((char *)pFrame + 0x20 + (ptrdiff_t)channelIndex * 0x10);

    if (!drflac__read_subframe_header(pFlac, pSubframe)) {
        return 0;
    }

    int wastedBitsPerSample = pSubframe->wasted_bits_per_sample;

    // Adjust wasted bits per sample based on channel assignment and index
    if ((pFrame->channel_assignment == 8 || pFrame->channel_assignment == 10) && channelIndex == 1) {
        wastedBitsPerSample += 1;
    } else if (pFrame->channel_assignment == 9 && channelIndex == 0) {
        wastedBitsPerSample += 1;
    }

    if (pSubframe->order < wastedBitsPerSample) {
        return 0;
    }

    int bitsToSeek = pSubframe->order - wastedBitsPerSample;
    pSubframe->reserved2 = 0;

    switch (pSubframe->reserved1) {
        case 0: // SUBFRAME_CONSTANT
            if (!drflac__seek_bits(pFlac, bitsToSeek)) {
                return 0;
            }
            break;

        case 1: // SUBFRAME_VERBATIM
            if (!drflac__seek_bits(pFlac, pFrame->blocksize * bitsToSeek)) {
                return 0;
            }
            break;

        case 2: // SUBFRAME_FIXED
            if (!drflac__seek_bits(pFlac, pSubframe->order * bitsToSeek)) {
                return 0;
            }
            if (!drflac__read_and_seek_residual__rice(pFlac, pFrame->blocksize, pSubframe->order)) {
                return 0;
            }
            break;

        case 3: // SUBFRAME_LPC
            if (!drflac__seek_bits(pFlac, pSubframe->order * bitsToSeek)) {
                return 0;
            }
            uint8_t lpcPrecision;
            if (!drflac__read_uint32(pFlac, 4, &lpcPrecision)) {
                return 0;
            }
            if (lpcPrecision == 15) {
                return 0;
            }
            lpcPrecision += 1;
            
            if (!drflac__seek_bits(pFlac, pSubframe->order * lpcPrecision + 5)) {
                return 0;
            }
            if (!drflac__read_and_seek_residual__rice(pFlac, pFrame->blocksize, pSubframe->order)) {
                return 0;
            }
            break;

        default:
            return 0;
    }

    return 1;
}