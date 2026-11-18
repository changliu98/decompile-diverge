BOOL __cdecl zgfx_decompress_segment(ZGFX_CONTEXT *zgfx, wStream *stream, size_t segmentSize)
{
  UINT32 v3; // eax
  UINT32 OutputCount; // ecx
  size_t cbSegment; // [rsp+0h] [rbp-50h]
  const BYTE *pbSegment; // [rsp+8h] [rbp-48h]
  int distance; // [rsp+14h] [rbp-3Ch]
  UINT32 count; // [rsp+18h] [rbp-38h]
  UINT32 counta; // [rsp+18h] [rbp-38h]
  UINT32 countb; // [rsp+18h] [rbp-38h]
  int inPrefix; // [rsp+1Ch] [rbp-34h]
  unsigned int haveBits; // [rsp+20h] [rbp-30h]
  int opIndex; // [rsp+24h] [rbp-2Ch]
  UINT32 extra; // [rsp+28h] [rbp-28h]
  BYTE flags; // [rsp+2Eh] [rbp-22h]
  BYTE c; // [rsp+2Fh] [rbp-21h]

  cbSegment = segmentSize - 1;
  if ( Stream_GetRemainingLength(stream) < segmentSize || !segmentSize )
    return 0;
  flags = *stream->pointer;
  Stream_Seek(stream, 1uLL);
  zgfx->OutputCount = 0;
  pbSegment = Stream_Pointer(stream);
  Stream_Seek(stream, cbSegment);
  if ( (flags & 0x20) != 0 )
  {
    zgfx->pbInputCurrent = pbSegment;
    zgfx->pbInputEnd = &pbSegment[cbSegment - 1];
    zgfx->cBitsRemaining = 8 * (cbSegment - 1) - *zgfx->pbInputEnd;
    zgfx->cBitsCurrent = 0;
    zgfx->BitsCurrent = 0;
LABEL_7:
    while ( zgfx->cBitsRemaining )
    {
      haveBits = 0;
      inPrefix = 0;
      for ( opIndex = 0; ZGFX_TOKEN_TABLE[5 * opIndex]; ++opIndex )
      {
        while ( haveBits < ZGFX_TOKEN_TABLE[5 * opIndex] )
        {
          zgfx_GetBits(zgfx, 1u);
          inPrefix = zgfx->bits + 2 * inPrefix;
          ++haveBits;
        }
        if ( inPrefix == ZGFX_TOKEN_TABLE[5 * opIndex + 1] )
        {
          if ( ZGFX_TOKEN_TABLE[5 * opIndex + 3] )
          {
            zgfx_GetBits(zgfx, ZGFX_TOKEN_TABLE[5 * opIndex + 2]);
            distance = zgfx->bits + ZGFX_TOKEN_TABLE[5 * opIndex + 4];
            if ( distance )
            {
              zgfx_GetBits(zgfx, 1u);
              if ( zgfx->bits )
              {
                counta = 4;
                extra = 2;
                zgfx_GetBits(zgfx, 1u);
                while ( zgfx->bits == 1 )
                {
                  counta *= 2;
                  ++extra;
                  zgfx_GetBits(zgfx, 1u);
                }
                zgfx_GetBits(zgfx, extra);
                count = counta + zgfx->bits;
                zgfx_history_buffer_ring_read(zgfx, distance, &zgfx->OutputBuffer[zgfx->OutputCount], count);
              }
              else
              {
                count = 3;
                zgfx_history_buffer_ring_read(zgfx, distance, &zgfx->OutputBuffer[zgfx->OutputCount], 3u);
              }
              zgfx_history_buffer_ring_write(zgfx, &zgfx->OutputBuffer[zgfx->OutputCount], count);
              zgfx->OutputCount += count;
            }
            else
            {
              zgfx_GetBits(zgfx, 0xFu);
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
            zgfx_GetBits(zgfx, ZGFX_TOKEN_TABLE[5 * opIndex + 2]);
            c = LOBYTE(zgfx->bits) + LOBYTE(ZGFX_TOKEN_TABLE[5 * opIndex + 4]);
            zgfx->HistoryBuffer[zgfx->HistoryIndex] = c;
            v3 = zgfx->HistoryIndex + 1;
            zgfx->HistoryIndex = v3;
            if ( v3 == zgfx->HistoryBufferSize )
              zgfx->HistoryIndex = 0;
            OutputCount = zgfx->OutputCount;
            zgfx->OutputCount = OutputCount + 1;
            zgfx->OutputBuffer[OutputCount] = c;
          }
          goto LABEL_7;
        }
      }
    }
    return 1;
  }
  else
  {
    zgfx_history_buffer_ring_write(zgfx, pbSegment, cbSegment);
    memcpy(zgfx->OutputBuffer, pbSegment, cbSegment);
    zgfx->OutputCount = cbSegment;
    return 1;
  }
}