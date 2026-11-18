drflac_bool32 drflac__seek_subframe(drflac_bs *bs, drflac_frame *frame, int subframeIndex)
{
    drflac_subframe *subframe;
    drflac_uint32 subframeBitsPerSample;

    do { if (!(bs != ((void*)0))) { __assert_fail("bs != ((void*)0)", "func.c", 5447, "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)"); } } while (0);
    do { if (!(frame != ((void*)0))) { __assert_fail("frame != ((void*)0)", "func.c", 5448, "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)"); } } while (0);

    subframe = &frame->subframes[subframeIndex];

    if (!drflac__read_subframe_header(bs, subframe)) {
        return 0;
    }

    subframeBitsPerSample = frame->header.bitsPerSample;
    if ((frame->header.channelAssignment == 8 || frame->header.channelAssignment == 10) && subframeIndex == 1) {
        subframeBitsPerSample += 1;
    } else if (frame->header.channelAssignment == 9 && subframeIndex == 0) {
        subframeBitsPerSample += 1;
    }

    if (subframe->wastedBitsPerSample >= subframeBitsPerSample) {
        return 0;
    }

    subframeBitsPerSample -= subframe->wastedBitsPerSample;
    subframe->pSamplesS32 = ((void*)0);

    switch (subframe->subframeType) {
        case 0:
            if (!drflac__seek_bits(bs, subframeBitsPerSample)) {
                return 0;
            }
            break;

        case 1:
            if (!drflac__seek_bits(bs, frame->header.blockSizeInPCMFrames * subframeBitsPerSample)) {
                return 0;
            }
            break;

        case 8:
            if (!drflac__seek_bits(bs, subframe->lpcOrder * subframeBitsPerSample)) {
                return 0;
            }

            if (!drflac__read_and_seek_residual(bs, frame->header.blockSizeInPCMFrames, subframe->lpcOrder)) {
                return 0;
            }
            break;

        case 32:
            if (!drflac__seek_bits(bs, subframe->lpcOrder * subframeBitsPerSample)) {
                return 0;
            }

            {
                drflac_uint8 lpcPrecision;
                if (!drflac__read_uint8(bs, 4, &lpcPrecision)) {
                    return 0;
                }

                if (lpcPrecision == 15) {
                    return 0;
                }

                lpcPrecision += 1;

                if (!drflac__seek_bits(bs, 5 + subframe->lpcOrder * lpcPrecision)) {
                    return 0;
                }
            }

            if (!drflac__read_and_seek_residual(bs, frame->header.blockSizeInPCMFrames, subframe->lpcOrder)) {
                return 0;
            }
            break;

        default:
            return 0;
    }

    return 1;
}