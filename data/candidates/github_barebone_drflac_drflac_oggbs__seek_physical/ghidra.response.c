drflac_bool32
drflac_oggbs__seek_physical(drflac_oggbs *oggbs,drflac_uint64 offset,drflac_seek_origin origin)

{
  drflac_bool32 dVar1;
  drflac_seek_origin origin_local;
  drflac_uint64 offset_local;
  drflac_oggbs *oggbs_local;
  drflac_bool32 local_c;
  
  offset_local = offset;
  if (origin == DRFLAC_SEEK_SET) {
    if (offset < 0x80000000) {
      dVar1 = (*oggbs->onSeek)(oggbs->pUserData,(int)offset,DRFLAC_SEEK_SET);
      if (dVar1 == 0) {
        local_c = 0;
      }
      else {
        oggbs->currentBytePos = offset;
        local_c = 1;
      }
    }
    else {
      dVar1 = (*oggbs->onSeek)(oggbs->pUserData,0x7fffffff,DRFLAC_SEEK_SET);
      if (dVar1 == 0) {
        local_c = 0;
      }
      else {
        oggbs->currentBytePos = offset;
        local_c = drflac_oggbs__seek_physical(oggbs,offset - 0x7fffffff,DRFLAC_SEEK_CUR);
      }
    }
  }
  else {
    for (; 0x7fffffff < offset_local; offset_local = offset_local - 0x7fffffff) {
      dVar1 = (*oggbs->onSeek)(oggbs->pUserData,0x7fffffff,DRFLAC_SEEK_CUR);
      if (dVar1 == 0) {
        return 0;
      }
      oggbs->currentBytePos = oggbs->currentBytePos + 0x7fffffff;
    }
    dVar1 = (*oggbs->onSeek)(oggbs->pUserData,(int)offset_local,DRFLAC_SEEK_CUR);
    if (dVar1 == 0) {
      local_c = 0;
    }
    else {
      oggbs->currentBytePos = offset_local + oggbs->currentBytePos;
      local_c = 1;
    }
  }
  return local_c;
}