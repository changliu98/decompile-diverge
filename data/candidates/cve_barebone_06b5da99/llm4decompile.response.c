BOOL zgfx_decompress_segment(ZGFX_CONTEXT *zgfx,wStream *stream,size_t segmentSize)
{
    BYTE *pbSegment;
    BYTE *pbSegmentEnd;
    BYTE bSegmentHeader;
    BYTE c;
    UINT32 cbSegment;
    UINT32 cbRemaining;
    UINT32 inPrefix;
    UINT32 haveBits;
    UINT32 opIndex;
    UINT32 offset;
    UINT32 count;
    UINT32 extra;

    cbSegment = segmentSize - 1;

    if (Stream_GetRemainingLength(stream) < segmentSize || segmentSize == 0)
    {
        return 0;
    }

    bSegmentHeader = *stream->pointer;
    Stream_Seek(stream,1);

    zgfx->OutputCount = 0;

    pbSegment = Stream_Pointer(stream);
    pbSegmentEnd = pbSegment + cbSegment;

    Stream_Seek(stream,cbSegment);

    if ((bSegmentHeader & 0x20) == 0)
    {
        zgfx_history_buffer_ring_write(zgfx,pbSegment,cbSegment);
        memcpy(zgfx->OutputBuffer,pbSegment,cbSegment);
        zgfx->OutputCount = cbSegment;
        return 1;
    }

    zgfx->pbInputCurrent = pbSegment;
    zgfx->pbInputEnd = pbSegmentEnd;
    zgfx->cBitsRemaining = (cbSegment - 1) * 8 - (*zgfx->pbInputEnd);
    zgfx->cBitsCurrent = 0;
    zgfx->BitsCurrent = 0;

    while (zgfx->cBitsRemaining)
    {
        inPrefix = 0;
        haveBits = 0;
        opIndex = 0;

        while (ZGFX_TOKEN_TABLE[opIndex].prefixLength)
        {
            while (haveBits < ZGFX_TOKEN_TABLE[opIndex].prefixLength)
            {
                zgfx_GetBits(zgfx,1);
                inPrefix = (inPrefix << 1) + zgfx->bits;
                haveBits++;
            }

            if (inPrefix == ZGFX_TOKEN_TABLE[opIndex].prefixCode)
            {
                if (ZGFX_TOKEN_TABLE[opIndex].tokenType == 0)
                {
                    zgfx_GetBits(zgfx,ZGFX_TOKEN_TABLE[opIndex].valueBits);
                    c = zgfx->bits + ZGFX_TOKEN_TABLE[opIndex].valueBase;
                    zgfx->HistoryBuffer[zgfx->HistoryIndex] = c;
                    zgfx->HistoryIndex++;
                    if (zgfx->HistoryIndex == zgfx->HistoryBufferSize)
                    {
                        zgfx->HistoryIndex = 0;
                    }
                    zgfx->OutputBuffer[zgfx->OutputCount++] = c;
                }
                else
                {
                    zgfx_GetBits(zgfx,ZGFX_TOKEN_TABLE[opIndex].valueBits);
                    offset = zgfx->bits + ZGFX_TOKEN_TABLE[opIndex].valueBase;

                    if (offset == 0)
                    {
                        zgfx_GetBits(zgfx,15);
                        count = zgfx->bits;
                        zgfx->cBitsRemaining -= zgfx->cBitsCurrent;
                        zgfx->cBitsCurrent = 0;
                        zgfx->BitsCurrent = 0;
                        memcpy(zgfx->OutputBuffer + zgfx->OutputCount,zgfx->pbInputCurrent,count);
                        zgfx_history_buffer_ring_write(zgfx,zgfx->pbInputCurrent,count);
                        zgfx->pbInputCurrent += count;
                        zgfx->cBitsRemaining -= count * 8;
                        zgfx->OutputCount += count;
                    }
                    else
                    {
                        zgfx_GetBits(zgfx,1);
                        if (zgfx->bits == 0)
                        {
                            count = 3;
                        }
                        else
                        {
                            count = 4;
                            extra = 2;
                            zgfx_GetBits(zgfx,1);
                            while (zgfx->bits == 1)
                            {
                                count <<= 1;
                                extra++;
                                zgfx_GetBits(zgfx,1);
                            }
                            zgfx_GetBits(zgfx,extra);
                            count += zgfx->bits;
                        }

                        zgfx_history_buffer_ring_read(zgfx,offset,zgfx->OutputBuffer + zgfx->OutputCount,count);
                        zgfx_history_buffer_ring_write(zgfx,zgfx->OutputBuffer + zgfx->OutputCount,count);
                        zgfx->OutputCount += count;
                    }
                }
                break;
            }
            opIndex++;
        }
    }

    return 1;
}