BOOL zgfx_decompress_segment(ZGFX_CONTEXT *zgfx,wStream *stream,size_t segmentSize)

{
  byte bVar1;
  uint uVar2;
  BYTE BVar3;
  UINT32 UVar4;
  int offset;
  size_t _offset;
  size_t sVar5;
  BYTE *src;
  size_t cbSegment;
  BYTE *pbSegment;
  UINT32 distance;
  UINT32 count;
  int inPrefix;
  int haveBits;
  int opIndex;
  UINT32 extra;
  BYTE flags;
  BYTE c;
  size_t segmentSize_local;
  wStream *stream_local;
  ZGFX_CONTEXT *zgfx_local;
  BOOL local_c;
  
  _offset = segmentSize - 1;
  sVar5 = Stream_GetRemainingLength(stream);
  if ((sVar5 < segmentSize) || (segmentSize == 0)) {
    local_c = 0;
  }
  else {
    bVar1 = *stream->pointer;
    Stream_Seek(stream,1);
    zgfx->OutputCount = 0;
    src = Stream_Pointer(stream);
    Stream_Seek(stream,_offset);
    if ((bVar1 & 0x20) == 0) {
      zgfx_history_buffer_ring_write(zgfx,src,_offset);
      memcpy(zgfx->OutputBuffer,src,_offset);
      zgfx->OutputCount = (UINT32)_offset;
      local_c = 1;
    }
    else {
      zgfx->pbInputCurrent = src;
      zgfx->pbInputEnd = src + (segmentSize - 2);
      zgfx->cBitsRemaining = ((UINT32)_offset - 1) * 8 - (uint)*zgfx->pbInputEnd;
      zgfx->cBitsCurrent = 0;
      zgfx->BitsCurrent = 0;
LAB_00101677:
      if (zgfx->cBitsRemaining != 0) {
        haveBits = 0;
        inPrefix = 0;
        opIndex = 0;
        while (ZGFX_TOKEN_TABLE[opIndex].prefixLength != 0) {
          for (; (uint)haveBits < ZGFX_TOKEN_TABLE[opIndex].prefixLength; haveBits = haveBits + 1) {
            zgfx_GetBits(zgfx,1);
            inPrefix = inPrefix * 2 + zgfx->bits;
          }
          if (inPrefix == ZGFX_TOKEN_TABLE[opIndex].prefixCode) {
            if (ZGFX_TOKEN_TABLE[opIndex].tokenType == 0) {
              zgfx_GetBits(zgfx,ZGFX_TOKEN_TABLE[opIndex].valueBits);
              BVar3 = (char)ZGFX_TOKEN_TABLE[opIndex].valueBase + (char)zgfx->bits;
              zgfx->HistoryBuffer[zgfx->HistoryIndex] = BVar3;
              UVar4 = zgfx->HistoryIndex + 1;
              zgfx->HistoryIndex = UVar4;
              if (UVar4 == zgfx->HistoryBufferSize) {
                zgfx->HistoryIndex = 0;
              }
              uVar2 = zgfx->OutputCount;
              zgfx->OutputCount = uVar2 + 1;
              zgfx->OutputBuffer[uVar2] = BVar3;
            }
            else {
              zgfx_GetBits(zgfx,ZGFX_TOKEN_TABLE[opIndex].valueBits);
              offset = ZGFX_TOKEN_TABLE[opIndex].valueBase + zgfx->bits;
              if (offset == 0) {
                zgfx_GetBits(zgfx,0xf);
                uVar2 = zgfx->bits;
                zgfx->cBitsRemaining = zgfx->cBitsRemaining - zgfx->cBitsCurrent;
                zgfx->cBitsCurrent = 0;
                zgfx->BitsCurrent = 0;
                memcpy(zgfx->OutputBuffer + zgfx->OutputCount,zgfx->pbInputCurrent,(ulong)uVar2);
                zgfx_history_buffer_ring_write(zgfx,zgfx->pbInputCurrent,(ulong)uVar2);
                zgfx->pbInputCurrent = zgfx->pbInputCurrent + uVar2;
                zgfx->cBitsRemaining = zgfx->cBitsRemaining + uVar2 * -8;
                zgfx->OutputCount = uVar2 + zgfx->OutputCount;
              }
              else {
                zgfx_GetBits(zgfx,1);
                if (zgfx->bits == 0) {
                  count = 3;
                }
                else {
                  count = 4;
                  extra = 2;
                  zgfx_GetBits(zgfx,1);
                  while (zgfx->bits == 1) {
                    count = count << 1;
                    extra = extra + 1;
                    zgfx_GetBits(zgfx,1);
                  }
                  zgfx_GetBits(zgfx,extra);
                  count = zgfx->bits + count;
                }
                zgfx_history_buffer_ring_read
                          (zgfx,offset,zgfx->OutputBuffer + zgfx->OutputCount,count);
                zgfx_history_buffer_ring_write
                          (zgfx,zgfx->OutputBuffer + zgfx->OutputCount,(ulong)count);
                zgfx->OutputCount = count + zgfx->OutputCount;
              }
            }
            break;
          }
          opIndex = opIndex + 1;
        }
        goto LAB_00101677;
      }
      local_c = 1;
    }
  }
  return local_c;
}