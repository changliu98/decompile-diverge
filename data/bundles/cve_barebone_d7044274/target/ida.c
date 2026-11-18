int __cdecl DGifSlurp(GifFileType *GifFile)
{
  unsigned int Width; // [rsp+8h] [rbp-B8h]
  unsigned int Height; // [rsp+Ch] [rbp-B4h]
  unsigned int j; // [rsp+10h] [rbp-B0h]
  unsigned int i; // [rsp+14h] [rbp-ACh]
  GifByteType *ExtData; // [rsp+18h] [rbp-A8h] BYREF
  SavedImage noext; // [rsp+20h] [rbp-A0h] BYREF
  SavedImage ext; // [rsp+60h] [rbp-60h] BYREF
  SavedImage *sp_0; // [rsp+A0h] [rbp-20h]
  GifRecordType RecordType; // [rsp+A8h] [rbp-18h] BYREF
  int ext_code; // [rsp+ACh] [rbp-14h] BYREF
  GifFileType *GifFilea; // [rsp+B0h] [rbp-10h]

  GifFilea = GifFile;
  sp_0 = 0LL;
  memset(&noext, 0, sizeof(noext));
  noext.delay = 0;
  noext.dispose = 0;
  noext.iter = 1;
  noext.transp = -1;
  noext.ExtensionBlocks = 0LL;
  noext.ExtensionBlockCount = 0;
  memcpy(&ext, &noext, sizeof(ext));
  GifFilea->SavedImages = 0LL;
  while ( 1 )
  {
    if ( !DGifGetRecordType(GifFilea, &RecordType) )
      return 0;
    if ( RecordType != IMAGE_DESC_RECORD_TYPE )
      break;
    if ( !DGifGetImageDesc(GifFilea) )
      return 0;
    sp_0 = &GifFilea->SavedImages[(__int64)(GifFilea->ImageCount - 1)];
    ext.RasterBits = sp_0->RasterBits;
    *(_QWORD *)&ext.ImageDesc.Left = *(_QWORD *)&sp_0->ImageDesc.Left;
    *(_QWORD *)&ext.ImageDesc.Width = *(_QWORD *)&sp_0->ImageDesc.Width;
    *(_QWORD *)&ext.ImageDesc.Interlace = *(_QWORD *)&sp_0->ImageDesc.Interlace;
    ext.ImageDesc.ColorMap = sp_0->ImageDesc.ColorMap;
    memcpy(sp_0, &ext, sizeof(SavedImage));
    memcpy(&ext, &noext, sizeof(ext));
    sp_0->RasterBits = (GifPixelType *)xmalloc(sp_0->ImageDesc.Height * (__int64)sp_0->ImageDesc.Width);
    if ( sp_0->ImageDesc.Interlace )
    {
      Height = sp_0->ImageDesc.Height;
      Width = sp_0->ImageDesc.Width;
      for ( i = 0; i < 4; ++i )
      {
        for ( j = DGifSlurp_InterlacedOffset[i]; j < Height; j += DGifSlurp_InterlacedJumps[i] )
        {
          if ( DGifGetLine(GifFilea, &sp_0->RasterBits[j * Width], Width) != 1 )
            return 0;
        }
      }
    }
    else if ( !DGifGetLine(GifFilea, sp_0->RasterBits, sp_0->ImageDesc.Height * sp_0->ImageDesc.Width) )
    {
      return 0;
    }
LABEL_40:
    if ( RecordType == TERMINATE_RECORD_TYPE )
      return 1;
  }
  if ( RecordType != EXTENSION_RECORD_TYPE )
    goto LABEL_40;
  if ( !DGifGetExtension(GifFilea, &ext_code, &ExtData) )
    return 0;
  if ( !ExtData )
    goto LABEL_40;
  if ( (unsigned __int8)ext_code != 249 )
  {
    if ( (unsigned __int8)ext_code != 255 )
    {
      AddExtensionBlock(&ext, *ExtData, ExtData + 1);
      ext.ExtensionBlocks[ext.ExtensionBlockCount - 1].code = ext_code;
      goto LABEL_36;
    }
    if ( *ExtData >= 4u )
    {
      ext.iter = *((_WORD *)ExtData + 1);
      goto LABEL_36;
    }
ext_too_short:
    GifError = 114;
    return 0;
  }
  if ( *ExtData < 4u )
    goto ext_too_short;
  ext.dispose = (int)ExtData[1] >> 2;
  ext.delay = *((_WORD *)ExtData + 1);
  if ( (ExtData[1] & 1) != 1 )
    goto LABEL_36;
  if ( *ExtData < 5u )
    goto ext_too_short;
  ext.transp = ExtData[4];
LABEL_36:
  while ( DGifGetExtensionNext(GifFilea, &ExtData) )
  {
    if ( !ExtData )
      goto LABEL_40;
    AddExtensionBlock(sp_0, *ExtData, ExtData + 1);
  }
  return 0;
}