int __cdecl DGifSlurp(GifFileType *GifFile)
{
  unsigned int Width, Height, j, i;
  GifByteType *ExtData;
  SavedImage noext, ext, *sp_0;
  GifRecordType RecordType;
  int ext_code;

  sp_0 = NULL;
  memset(&noext, 0, sizeof(noext));
  noext.delay = 0;
  noext.dispose = 0;
  noext.iter = 1;
  noext.transp = -1;
  noext.ExtensionBlocks = NULL;
  noext.ExtensionBlockCount = 0;
  memcpy(&ext, &noext, sizeof(ext));
  
  GifFile->SavedImages = NULL;

  while (1)
  {
    if (!DGifGetRecordType(GifFile, &RecordType))
      return 0;

    if (RecordType == IMAGE_DESC_RECORD_TYPE)
    {
      if (!DGifGetImageDesc(GifFile))
        return 0;

      sp_0 = &GifFile->SavedImages[GifFile->ImageCount - 1];
      
      // Preserve RasterBits and ImageDesc from the newly fetched image
      ext.RasterBits = sp_0->RasterBits;
      *(_QWORD *)&ext.ImageDesc.Left = *(_QWORD *)&sp_0->ImageDesc.Left;
      *(_QWORD *)&ext.ImageDesc.Width = *(_QWORD *)&sp_0->ImageDesc.Width;
      *(_QWORD *)&ext.ImageDesc.Interlace = *(_QWORD *)&sp_0->ImageDesc.Interlace;
      ext.ImageDesc.ColorMap = sp_0->ImageDesc.ColorMap;
      
      // Apply parsed extension data to the saved image, then reset ext
      memcpy(sp_0, &ext, sizeof(SavedImage));
      memcpy(&ext, &noext, sizeof(ext));

      sp_0->RasterBits = (GifPixelType *)xmalloc(sp_0->ImageDesc.Height * (__int64)sp_0->ImageDesc.Width);

      if (sp_0->ImageDesc.Interlace)
      {
        Height = sp_0->ImageDesc.Height;
        Width = sp_0->ImageDesc.Width;
        for (i = 0; i < 4; ++i)
        {
          for (j = DGifSlurp_InterlacedOffset[i]; j < Height; j += DGifSlurp_InterlacedJumps[i])
          {
            if (DGifGetLine(GifFile, &sp_0->RasterBits[j * Width], Width) != 1)
              return 0;
          }
        }
      }
      else if (!DGifGetLine(GifFile, sp_0->RasterBits, sp_0->ImageDesc.Height * sp_0->ImageDesc.Width))
      {
        return 0;
      }
    }
    else if (RecordType == EXTENSION_RECORD_TYPE)
    {
      if (!DGifGetExtension(GifFile, &ext_code, &ExtData))
        return 0;

      if (!ExtData)
        continue;

      if ((unsigned __int8)ext_code == 249) // Graphics Control Extension
      {
        if (*ExtData < 4u)
          goto ext_too_short;
        
        ext.dispose = (int)ExtData[1] >> 2;
        ext.delay = *((_WORD *)ExtData + 1);
        
        if ((ExtData[1] & 1) == 1)
        {
          if (*ExtData < 5u)
            goto ext_too_short;
          ext.transp = ExtData[4];
        }
      }
      else if ((unsigned __int8)ext_code == 255) // Application Extension
      {
        if (*ExtData >= 4u)
          ext.iter = *((_WORD *)ExtData + 1);
        else
          goto ext_too_short;
      }
      else // Generic Extension
      {
        AddExtensionBlock(&ext, *ExtData, ExtData + 1);
        ext.ExtensionBlocks[ext.ExtensionBlockCount - 1].code = ext_code;
      }

      while (DGifGetExtensionNext(GifFile, &ExtData))
      {
        if (!ExtData)
          break;
        AddExtensionBlock(sp_0, *ExtData, ExtData + 1);
      }
    }
    else if (RecordType == TERMINATE_RECORD_TYPE)
    {
      return 1;
    }
  }

ext_too_short:
  GifError = 114;
  return 0;
}