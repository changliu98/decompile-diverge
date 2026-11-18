drmp3_bool32 drmp3__on_seek_64(drmp3 *pMP3,drmp3_uint64 offset,drmp3_seek_origin origin)

{
  drmp3_bool32 dVar1;
  drmp3_seek_origin origin_local;
  drmp3_uint64 offset_local;
  drmp3 *pMP3_local;
  drmp3_bool32 local_c;
  
  if (offset < 0x80000000) {
    local_c = drmp3__on_seek(pMP3,(int)offset,origin);
  }
  else {
    dVar1 = drmp3__on_seek(pMP3,0x7fffffff,DRMP3_SEEK_SET);
    if (dVar1 == 0) {
      local_c = 0;
    }
    else {
      offset_local = offset - 0x7fffffff;
      while (offset_local != 0) {
        if (offset_local < 0x80000000) {
          dVar1 = drmp3__on_seek(pMP3,(int)offset_local,DRMP3_SEEK_CUR);
          if (dVar1 == 0) {
            return 0;
          }
          offset_local = 0;
        }
        else {
          dVar1 = drmp3__on_seek(pMP3,0x7fffffff,DRMP3_SEEK_CUR);
          if (dVar1 == 0) {
            return 0;
          }
          offset_local = offset_local - 0x7fffffff;
        }
      }
      local_c = 1;
    }
  }
  return local_c;
}