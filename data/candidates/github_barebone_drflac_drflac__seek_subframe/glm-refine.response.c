drflac_bool32 __cdecl drflac__seek_subframe(drflac_bs *bs, drflac_frame *frame, int subframeIndex)
{
    drflac_uint8 lpcPrecision;
    unsigned int bitsToSeek;
    drflac_uint32 subframeBitsPerSample;
    drflac_subframe *pSubframe;

    assert(bs != NULL);
    assert(frame != NULL);

    pSubframe = &frame->subframes[subframeIndex];
    
    if (!drflac__read_subframe_header(bs, pSubframe)) {
        return 0;
    }

    subframeBitsPerSample = frame->header.bitsPerSample;
    
    // Adjust bits per sample for side channels in mid-side stereo
    if ((frame->header.channelAssignment == 8 || frame->header.channelAssignment == 10) && subframeIndex == 1) {
        subframeBitsPerSample++;
    } else if (frame->header.channelAssignment == 9 && subframeIndex == 0) {
        subframeBitsPerSample++;
    }

    if (pSubframe->wastedBitsPerSample >= subframeBitsPerSample) {
        return 0;
    }
    
    subframeBitsPerSample -= pSubframe->wastedBitsPerSample;
    pSubframe->pSamplesS32 = NULL;

    switch (pSubframe->subframeType)
    {
        case 0u: // Constant
            if (drflac__seek_bits(bs, subframeBitsPerSample))
                return 1;
            return 0;

        case 1u: // Verbatim
            if (drflac__seek_bits(bs, subframeBitsPerSample * frame->header.blockSizeInPCMFrames))
                return 1;
            return 0;

        case 8u: // Fixed LPC
            bitsToSeek = subframeBitsPerSample * pSubframe->lpcOrder;
            if (!drflac__seek_bits(bs, bitsToSeek))
                return 0;
            if (drflac__read_and_seek_residual(bs, frame->header.blockSizeInPCMFrames, pSubframe->lpcOrder))
                return 1;
            return 0;

        case 0x20u: // FIR LPC
            if (!drflac__seek_bits(bs, subframeBitsPerSample * pSubframe->lpcOrder))
                return 0;
            if (!drflac__read_uint8(bs, 4u, &lpcPrecision))
                return 0;
            if (lpcPrecision == 15)
                return 0;
            
            lpcPrecision++;
            if (!drflac__seek_bits(bs, lpcPrecision * (unsigned int)pSubframe->lpcOrder + 5))
                return 0;
            if (drflac__read_and_seek_residual(bs, frame->header.blockSizeInPCMFrames, pSubframe->lpcOrder))
                return 1;
            return 0;

        default:
            return 0;
    }
}