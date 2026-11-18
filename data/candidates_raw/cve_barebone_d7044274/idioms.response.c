int DGifSlurp(struct _GifFileType *pGifFile)
{
  struct _SavedImage *pSaved = ((void *)0);
  struct _SavedImage noext;
  struct _SavedImage ext;
  struct _GifRecordType RecordType;
  int ExtCode;
  unsigned char *ExtData;
  int i;
  int j;
  int width;
  int height;
  DGifImageInit(&noext);
  noext.delay = 0;
  noext.dispose = 0;
  noext.iter = 1;
  noext.transp = -1;
  noext.ExtensionBlocks = ((void *)0);
  noext.ExtensionBlockCount = 0;
  DGifImageInitEx(&ext, &noext);
  pGifFile->SavedImages = ((void *)0);
  while (DGifGetRecordType(pGifFile, &RecordType))
  {
    switch (RecordType.Type)
    {
      case IMAGE_DESC_RECORD_TYPE:
        if (!DGifGetImageDesc(pGifFile))
          return (0);
        pSaved = &pGifFile->SavedImages[pGifFile->ImageCount - 1];
        ext.RasterBits = pSaved->RasterBits;
        ext.ImageDesc = pSaved->ImageDesc;
        DGifImageInitEx(pSaved, &ext);
        DGifImageInitEx(&ext, &noext);
        pSaved->RasterBits =
          (unsigned char *)DGifImageCreateRaster(pSaved->ImageDesc.Width,
            pSaved->ImageDesc.Height);
        if (pSaved->ImageDesc.Interlace)
        {
          height = pSaved->ImageDesc.Height;
          width = pSaved->ImageDesc.Width;
          for (i = 0; i < 4; i++)
          {
            for (j = DGifSlurp_InterlacedOffset[i];
              j < height;
              j += DGifSlurp_InterlacedJumps[i])
            {
              if (!DGifGetLine(pGifFile,
                &pSaved->RasterBits[j * width],
                width))
                return (0);
            }
          }
        }
        else
        {
          if (!DGifGetLine(pGifFile,
            pSaved->RasterBits,
            pSaved->ImageDesc.Width * pSaved->ImageDesc.Height))
            return (0);
        }
        break;
      case TERMINATE_RECORD_TYPE:
        return (1);
      case EXTENSION_RECORD_TYPE:
        if (!DGifGetExtension(pGifFile, &ExtCode, &ExtData))
          return (0);
        if (ExtData == ((void *)0))
          break;
        if (ExtCode == 0xf9)
        {
          if (ExtData[0] < 4)
            goto ext_too_short;
          ext.dispose = (int)(ExtData[1] >> 2);
          ext.delay = (int)(ExtData[2] + (ExtData[3] << 8));
          if (ExtData[1] & 1)
          {
            if (ExtData[0] < 5)
              goto ext_too_short;
            ext.transp = (int)(ExtData[4]);
          }
        }
        else if (ExtCode == 0xff)
        {
          if (ExtData[0] < 4)
            goto ext_too_short;
          ext.iter = (int)(ExtData[1] + (ExtData[2] << 8));
        }
        else
        {
          DGifGetExtensionNext(pGifFile, &ExtData);
          if (ExtData == ((void *)0))
            break;
          DGifImageAddExtension(&ext, ExtData[0], &ExtData[1]);
          ext.ExtensionBlocks[ext.ExtensionBlockCount - 1].code = ExtCode;
        }
        while (DGifGetExtensionNext(pGifFile, &ExtData))
        {
          if (ExtData == ((void *)0))
            break;
          DGifImageAddExtension(pSaved, ExtData[0], &ExtData[1]);
        }
        return (0);
    }
  }
  return (0);
}