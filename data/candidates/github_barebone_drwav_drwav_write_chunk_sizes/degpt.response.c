void drwav_write_chunk_sizes(drwav *pWav)

{
  drwav_bool32 dVar1;
  drwav_uint32 dVar2;
  drwav_uint64 dVar3;
  drwav_uint64 dataChunkSize_2;
  drwav_uint64 riffChunkSize_2;
  int ds64BodyPos;
  drwav_uint64 dataChunkSize_1;
  drwav_uint64 riffChunkSize_1;
  drwav_uint32 dataChunkSize;
  drwav_uint32 riffChunkSize;
  drwav *pWav_local;
  
  if ((pWav->onSeek != (drwav_seek_proc)0x0) && (pWav->isSequentialWrite == 0)) {
    if (pWav->container == drwav_container_riff) {
      dVar1 = (*pWav->onSeek)(pWav->pUserData,4,DRWAV_SEEK_SET);
      if (dVar1 != 0) {
        dVar2 = drwav__riff_chunk_size_riff
                          (pWav->dataChunkDataSize,pWav->pMetadata,pWav->metadataCount);
        drwav__write_u32ne_to_le(pWav,dVar2);
      }
      dVar1 = (*pWav->onSeek)(pWav->pUserData,(int)pWav->dataChunkDataPos + -4,DRWAV_SEEK_SET);
      if (dVar1 != 0) {
        dVar2 = drwav__data_chunk_size_riff(pWav->dataChunkDataSize);
        drwav__write_u32ne_to_le(pWav,dVar2);
      }
    }
    else if (pWav->container == drwav_container_w64) {
      dVar1 = (*pWav->onSeek)(pWav->pUserData,0x10,DRWAV_SEEK_SET);
      if (dVar1 != 0) {
        dVar3 = drwav__riff_chunk_size_w64(pWav->dataChunkDataSize);
        drwav__write_u64ne_to_le(pWav,dVar3);
      }
      dVar1 = (*pWav->onSeek)(pWav->pUserData,(int)pWav->dataChunkDataPos + -8,DRWAV_SEEK_SET);
      if (dVar1 != 0) {
        dVar3 = drwav__data_chunk_size_w64(pWav->dataChunkDataSize);
        drwav__write_u64ne_to_le(pWav,dVar3);
      }
    }
    else if (pWav->container == drwav_container_rf64) {
      dVar1 = (*pWav->onSeek)(pWav->pUserData,0x14,DRWAV_SEEK_SET);
      if (dVar1 != 0) {
        dVar3 = drwav__riff_chunk_size_rf64
                          (pWav->dataChunkDataSize,pWav->pMetadata,pWav->metadataCount);
        drwav__write_u64ne_to_le(pWav,dVar3);
      }
      dVar1 = (*pWav->onSeek)(pWav->pUserData,0x1c,DRWAV_SEEK_SET);
      if (dVar1 != 0) {
        dVar3 = drwav__data_chunk_size_rf64(pWav->dataChunkDataSize);
        drwav__write_u64ne_to_le(pWav,dVar3);
      }
    }
  }
  return;
}