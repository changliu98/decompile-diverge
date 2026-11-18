drflac_bool32 drflac__seek_subframe(drflac_bs *oggbs, drflac_frame *frame, int subframeIndex)
{
    drflac_subframe *pSubframe;
    unsigned int bitsPerSample;
    drflac_bool32 result;

    do { if (oggbs != ((void*)0)) {} else { ___assert_fail("oggbs != ((void*)0)", "./func.c", 5447, "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)"); } } while (0);
    do { if (frame != ((void*)0)) {} else { ___assert_fail("frame != ((void*)0)", "./func.c", 5448, "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)"); } } while (0);

    pSubframe = &frame->subframes[subframeIndex];

    if (!drflac__read_subframe_header(oggbs, pSubframe))
    {
        return 0;
    }

    bitsPerSample = frame->header.bitsPerSample;
    if ((frame->header.channelAssignment == 8 || frame->header.channelAssignment == 10) && (subframeIndex == 1))
    {
        bitsPerSample += 1;
    }
    else if (frame->header.channelAssignment == 9 && (subframeIndex == 0))
    {
        bitsPerSample += 1;
    }

    if (pSubframe->header.subframeType <= 1)
    {
        unsigned int bitsToSeek;
        if (pSubframe->header.subframeType == 0)
        {
            bitsToSeek = (unsigned int)(bitsPerSample - pSubframe->header.subframeBitsPerSample);
        }
        else
        {
            bitsToSeek = (unsigned int)(bitsPerSample - pSubframe->header.subframeBitsPerSample + 1);
        }

        if (bitsToSeek > 0)
        {
            pSubframe->crc8 = 0;
            switch (pSubframe->header.subframeType)
            {
                case 0:
                {
                    if (!drflac__seek_bits(oggbs, bitsToSeek))
                    {
                        return 0;
                    }
                }
                break;

                case 1:
                {
                    unsigned int bitsPerSampleForPredictor = (unsigned int)frame->header.blockSize * bitsPerSample;
                    if (!drflac__seek_bits(oggbs, bitsPerSampleForPredictor))
                    {
                        return 0;
                    }
                }
                break;

                case 8:
                {
                    unsigned int bitsPerSampleForRice = (unsigned int)pSubframe->header.ricePartitionSizeInBits * bitsPerSample;
                    if (!drflac__seek_bits(oggbs, bitsPerSampleForRice))
                    {
                        return 0;
                    }

                    if (!drflac__read_and_seek_residual(oggbs, (unsigned short)frame->header.blockSize, (unsigned char)pSubframe->header.ricePartitionSizeInBits))
                    {
                        return 0;
                    }
                }
                break;

                case 32:
                {
                    unsigned int bitsPerSampleForLPC = (unsigned int)pSubframe->header.ricePartitionSizeInBits * bitsPerSample;
                    if (!drflac__seek_bits(oggbs, bitsPerSampleForLPC))
                    {
                        return 0;
                    }

                    unsigned char lpcPrecision;
                    if (!drflac__read_uint8(oggbs, &lpcPrecision))
                    {
                        return 0;
                    }
                    if (lpcPrecision == 15)
                    {
                        return 0;
                    }
                    lpcPrecision += 1;

                    unsigned int bitsPerSampleForLPCPacked = (unsigned int)pSubframe->header.ricePartitionSizeInBits * lpcPrecision + 5;
                    if (!drflac__seek_bits(oggbs, bitsPerSampleForLPCPacked))
                    {
                        return 0;
                    }

                    if (!drflac__read_and_seek_residual(oggbs, (unsigned short)frame->header.blockSize, (unsigned char)pSubframe->header.ricePartitionSizeInBits))
                    {
                        return 0;
                    }
                }
                break;

                default:
                {
                    result = 0;
                    goto done;
                }
            }
        }
    }
    else
    {
        result = 0;
        goto done;
    }

    result = 1;

done:
    return result;
}