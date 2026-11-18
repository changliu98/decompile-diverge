drflac_bool32 drflac__seek_to_byte(drflac_bs *bs,drflac_uint64 offsetFromStart)

{
  drflac_bool32 dVar1;
  drflac_uint64 bytesRemaining;
  drflac_uint64 offsetFromStart_local;
  drflac_bs *bs_local;
  drflac_bool32 local_c;
  
  if (bs == (drflac_bs *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("bs != ((void*)0)","func.c",0xb41,
                  "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
  }
  if (offsetFromStart == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("offsetFromStart > 0","func.c",0xb42,
                  "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
  }
  if (offsetFromStart < 0x80000000) {
    dVar1 = (*bs->onSeek)(bs->pUserData,(int)offsetFromStart,DRFLAC_SEEK_SET);
    if (dVar1 == 0) {
      local_c = 0;
    }
    else {
LAB_0012965d:
      drflac__reset_cache(bs);
      local_c = 1;
    }
  }
  else {
    dVar1 = (*bs->onSeek)(bs->pUserData,0x7fffffff,DRFLAC_SEEK_SET);
    if (dVar1 == 0) {
      local_c = 0;
    }
    else {
      do {
        bytesRemaining = offsetFromStart - 0x7fffffff;
        if (bytesRemaining < 0x80000000) {
          if ((bytesRemaining != 0) &&
             (dVar1 = (*bs->onSeek)(bs->pUserData,(int)bytesRemaining,DRFLAC_SEEK_CUR), dVar1 == 0))
          {
            return 0;
          }
          goto LAB_0012965d;
        }
        dVar1 = (*bs->onSeek)(bs->pUserData,0x7fffffff,DRFLAC_SEEK_CUR);
        offsetFromStart = bytesRemaining;
      } while (dVar1 != 0);
      local_c = 0;
    }
  }
  return local_c;
}