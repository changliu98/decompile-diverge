int
DGifSlurp(GifFileType *GifFileIn)
{
    SavedImage *New;
    ExtensionBlock *ep;
    int i, ImageNum = 0, CodeSize, InterlacedStart, InterlacedJump;
    unsigned char *buf;
    int lpr, pr;

    New = NULL;

    memset(&GlobalColorMap, 0, sizeof(ColorMapType));
    memset(&LocalColorMap, 0, sizeof(ColorMapType));

    memset(&ImageDesc, 0, sizeof(ImageDescType));
    ImageDesc.ColorMap = NULL;

    memset(&ExtensionBlock, 0, sizeof(ExtensionBlock));

    memcpy(&GlobalColorMap, &LocalColorMap, sizeof(ColorMapType));
    GifFileIn->ImageCount = 0;

    do {
 if (DGifGetRecordType(GifFileIn, &CodeSize) == 0)
     return (0);
 switch (CodeSize) {
 case IMAGE_DESC_RECORD_TYPE:
     if (DGifGetImageDesc(GifFileIn) == 0)
  return (0);

     New = &GifFileIn->SavedImages[GifFileIn->ImageCount];
     memcpy(New, &ImageDesc, sizeof(SavedImage));
     memcpy(&ImageDesc, &GlobalColorMap, sizeof(ColorMapType));
     memcpy(&ImageDesc.ColorMap, &LocalColorMap,
     sizeof(ColorMapType));

     New->RasterBits = (char *)xmalloc((long)New->ImageDesc.Width *
         (long)New->ImageDesc.Height *
         sizeof(char));
     if (!New->Interlace) {
  if (DGifGetLine(GifFileIn, New->RasterBits,
    New->ImageDesc.Width *
    New->ImageDesc.Height) == 0)
      return (0);
     } else {
  lpr = New->ImageDesc.Height;
  pr = New->ImageDesc.Width;
  for (i = 0; i < 4; i++) {
      InterlacedStart = DGifSlurp_InterlacedOffset[i];
      while (InterlacedStart < lpr) {
   if (DGifGetLine(GifFileIn,
     &New->RasterBits[InterlacedStart * pr],
     pr) != 1)
       return (0);
   InterlacedStart += DGifSlurp_InterlacedJumps[i];
      }
  }
     }
     GifFileIn->ImageCount++;
     break;
 case EXTENSION_RECORD_TYPE:
     if (DGifGetExtension(GifFileIn, &ep, &buf) == 0)
  return (0);
     if (ep) {
  if (ep->Function == 0xf9) {
      if (ep->Bytes[0] < 4) {
   _GifError = 114;
   return (0);
      }
      ImageDesc.DisposalMode = ep->Bytes[0] >> 2;
      ImageDesc.DelayTime = ((unsigned short)ep->Bytes[2] << 8) | ep->Bytes[1];
      if ((ep->Bytes[0] & 1) == 1) {
   if (ep->Bytes[0] < 5) {
       _GifError = 114;
       return (0);
   }
   ImageDesc.TransparentColor =
       ((unsigned short)ep->Bytes[4] << 8) | ep->Bytes[3];
      }
  } else if (ep->Function == 0xff) {
      if (ep->Bytes[0] < 5) {
   _GifError = 114;
   return (0);
      }
      ImageDesc.iteration_count = ((unsigned short)ep->Bytes[2] << 8) | ep->Bytes[1];
  } else {
      AddExtensionBlock(&ExtensionBlock, ep->Bytes[0],
          &ep->Bytes[1]);
      ExtensionBlock.Function = ep->Function;
  }
  while (buf) {
      if (DGifGetExtensionNext(GifFileIn, &buf) == 0)
   return (0);
      if (buf)
   AddExtensionBlock(&ExtensionBlock, buf[0],
       &buf[1]);
  }
     }
     break;
 case TERMINATE_RECORD_TYPE:
     break;
 default:
     return (0);
 }
    } while (CodeSize != TERMINATE_RECORD_TYPE);

    return (1);
}