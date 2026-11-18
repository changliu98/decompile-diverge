BOOL __cdecl zgfx_decompress_segment(ZGFX_CONTEXT *zgfx, wStream *stream, size_t segmentSize)
{
    size_t cbSegment;
    const BYTE *pbSegment;
    BYTE flags;

    if (!segmentSize || Stream_GetRemainingLength(stream) < segmentSize)
        return FALSE;

    cbSegment = segmentSize - 1;
    flags = *stream->pointer;
    Stream_Seek(stream, 1);

    zgfx->OutputCount = 0;
    pbSegment = Stream_Pointer(stream);
    Stream_Seek(stream, cbSegment);

    // Uncompressed segment
    if (!(flags & 0x20))
    {
        zgfx_history_buffer_ring_write(zgfx, pbSegment, cbSegment);
        memcpy(zgfx->OutputBuffer, pbSegment, cbSegment);
        zgfx->OutputCount = cbSegment;
        return TRUE;
    }

    // Compressed segment
    zgfx->pbInputCurrent = pbSegment;
    zgfx->pbInputEnd = &pbSegment[cbSegment - 1];
    zgfx->cBitsRemaining = 8 * (cbSegment - 1) - *zgfx->pbInputEnd;
    zgfx->cBitsCurrent = 0;
    zgfx->BitsCurrent = 0;

    while (zgfx->cBitsRemaining > 0)
    {
        UINT32 haveBits = 0;
        UINT32 inPrefix = 0;
        int opIndex;

        for (opIndex = 0; ZGFX_TOKEN_TABLE[opIndex].prefixLength != 0; opIndex++)
        {
            ZGFX_TOKEN *token = &ZGFX_TOKEN_TABLE[opIndex];

            while (haveBits < token->prefixLength)
            {
                zgfx_GetBits(zgfx, 1);
                inPrefix = zgfx->bits + 2 * inPrefix;
                haveBits++;
            }

            if (inPrefix == token->prefixCode)
            {
                if (token->isMatch)
                {
                    zgfx_GetBits(zgfx, token->valueBits);
                    int distance = zgfx->bits + token->valueBase;

                    if (distance != 0)
                    {
                        UINT32 count;
                        zgfx_GetBits(zgfx, 1);

                        if (zgfx->bits)
                        {
                            UINT32 extra = 2;
                            count = 4;
                            zgfx_GetBits(zgfx, 1);

                            while (zgfx->bits == 1)
                            {
                                count *= 2;
                                extra++;
                                zgfx_GetBits(zgfx, 1);
                            }

                            zgfx_GetBits(zgfx, extra);
                            count += zgfx->bits;
                        }
                        else
                        {
                            count = 3;
                        }

                        zgfx_history_buffer_ring_read(zgfx, distance, &zgfx->OutputBuffer[zgfx->OutputCount], count);
                        zgfx_history_buffer_ring_write(zgfx, &zgfx->OutputBuffer[zgfx->OutputCount], count);
                        zgfx->OutputCount += count;
                    }
                    else
                    {
                        UINT32 countb;
                        zgfx_GetBits(zgfx, 15);
                        countb = zgfx->bits;

                        zgfx->cBitsRemaining -= zgfx->cBitsCurrent;
                        zgfx->cBitsCurrent = 0;
                        zgfx->BitsCurrent = 0;

                        memcpy(&zgfx->OutputBuffer[zgfx->OutputCount], zgfx->pbInputCurrent, countb);
                        zgfx_history_buffer_ring_write(zgfx, zgfx->pbInputCurrent, countb);

                        zgfx->pbInputCurrent += countb;
                        zgfx->cBitsRemaining -= 8 * countb;
                        zgfx->OutputCount += countb;
                    }
                }
                else
                {
                    zgfx_GetBits(zgfx, token->valueBits);
                    BYTE c = (BYTE)zgfx->bits + (BYTE)token->valueBase;

                    zgfx->HistoryBuffer[zgfx->HistoryIndex] = c;
                    if (++zgfx->HistoryIndex == zgfx->HistoryBufferSize)
                        zgfx->HistoryIndex = 0;

                    zgfx->OutputBuffer[zgfx->OutputCount++] = c;
                }
                break; // Equivalent to goto LABEL_7
            }
        }
    }

    return TRUE;
}