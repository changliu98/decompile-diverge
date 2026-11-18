static bool zgfx_decompress_frame(uint8 *frame, Stream *s, size_t cbSegment)
{
 uint8 flags;
 uint8 *pbSegment;
 size_t cbSegmentLeft;
 bool fDone;
 int iToken;
 int cExtra = 0;

 cbSegmentLeft = cbSegment - 1;

 if (Stream_GetRemainingLength(s) < cbSegment || cbSegment < 2)
 {
  fDone = false;
  goto exit;
 }

 while (true)
 {
  flags = *(uint8 *)s->ptr;
  Stream_Seek(s, 1);

  frame[0x4000 + 1] = 0;

  pbSegment = Stream_Pointer(s);
  Stream_Seek(s, cbSegmentLeft);

  if ((flags & 0x20) == 0)
  {

   zgfx_history_buffer_ring_write(frame, pbSegment, cbSegmentLeft);
   memcpy(&frame[10], pbSegment, cbSegmentLeft);
   frame[0x4000 + 1] = (uint8)cbSegmentLeft;
   fDone = true;
   break;
  }
  else
  {

   frame[2] = (uint8)(uintptr)pbSegment;
   frame[4] = (uint8)((uintptr)pbSegment + (cbSegmentLeft - 1));
   frame[7] = (uint8)((cbSegmentLeft - 1) * 8 - frame[4]);
   frame[9] = 0;
   frame[8] = 0;
  }

  while (true)
  {
   if (frame[7] == 0)
   {
    fDone = true;
    break;
   }

   int cHaveBits = 0;
   int prefix = 0;
   int iToken = 0;

   while (true)
   {
    if (ZGFX_TOKEN_TABLE[iToken].cBits == 0)
     break;

    while (true)
    {
     if (cHaveBits >= ZGFX_TOKEN_TABLE[iToken].cBits)
      break;

     zgfx_GetBits(frame, 1);
     prefix = (prefix << 1) + frame[6];
     cHaveBits++;
    }

    if (prefix == ZGFX_TOKEN_TABLE[iToken].prefix)
    {
     if (ZGFX_TOKEN_TABLE[iToken].cBits == 0)
     {

      uint8 b = (uint8)(zgfx_GetBits(frame, ZGFX_TOKEN_TABLE[iToken].cExtra) + ZGFX_TOKEN_TABLE[iToken].cOffset);

      frame[frame[0x9C96F1]] = b;
      frame[0x9C96F1]++;

      if (frame[0x9C96F1] == frame[0x9C96F2])
       frame[0x9C96F1] = 0;

      frame[frame[0x4000 + 1]++] = b;
     }
     else
     {

      int distance = (uint8)(zgfx_GetBits(frame, ZGFX_TOKEN_TABLE[iToken].cExtra) + ZGFX_TOKEN_TABLE[iToken].cOffset);

      if (distance != 0)
      {
       int cCopy;

       zgfx_GetBits(frame, 1);

       if (frame[6] == 0)
       {
        cCopy = 3;
       }
       else
       {
        cCopy = 4;
        cExtra = 2;
        zgfx_GetBits(frame, 1);

        while (true)
        {
         if (frame[6] != 1)
          break;

         cCopy <<= 1;
         cExtra++;
         zgfx_GetBits(frame, 1);
        }

        zgfx_GetBits(frame, cExtra);
        cCopy += frame[6];
       }

       zgfx_history_buffer_ring_read(frame, distance, &frame[10 + frame[0x4000 + 1]], cCopy);
       zgfx_history_buffer_ring_write(frame, &frame[10 + frame[0x4000 + 1]], cCopy);
       frame[0x4000 + 1] += cCopy;
      }
      else
      {

       int cCopy = zgfx_GetBits(frame, 15);

       cCopy = frame[6];

       frame[7] -= frame[9];
       frame[9] = 0;
       frame[8] = 0;

       memcpy(&frame[10 + frame[0x4000 + 1]], frame[2], cCopy);
       zgfx_history_buffer_ring_write(frame, frame[2], cCopy);
       frame[2] += cCopy;
       frame[7] -= cCopy * 8;
       frame[0x4000 + 1] += cCopy;
      }
     }
     break;
    }
   }
  }
 }

exit:
 return fDone;
}