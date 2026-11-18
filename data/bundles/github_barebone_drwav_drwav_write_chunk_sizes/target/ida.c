void __cdecl drwav_write_chunk_sizes(drwav *pWav)
{
  drwav_uint64 dataChunkSize_1; // [rsp+8h] [rbp-38h]
  drwav_uint64 riffChunkSize_1; // [rsp+10h] [rbp-30h]
  drwav_uint64 dataChunkSize_0; // [rsp+20h] [rbp-20h]
  drwav_uint64 riffChunkSize_0; // [rsp+28h] [rbp-18h]
  drwav_uint32 dataChunkSize; // [rsp+30h] [rbp-10h]
  drwav_uint32 riffChunkSize; // [rsp+34h] [rbp-Ch]

  if ( pWav->onSeek && !pWav->isSequentialWrite )
  {
    if ( pWav->container )
    {
      if ( pWav->container == drwav_container_w64 )
      {
        if ( pWav->onSeek(pWav->pUserData, 16, DRWAV_SEEK_SET) )
        {
          riffChunkSize_0 = drwav__riff_chunk_size_w64(pWav->dataChunkDataSize);
          drwav__write_u64ne_to_le(pWav, riffChunkSize_0);
        }
        if ( pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 8, DRWAV_SEEK_SET) )
        {
          dataChunkSize_0 = drwav__data_chunk_size_w64(pWav->dataChunkDataSize);
          drwav__write_u64ne_to_le(pWav, dataChunkSize_0);
        }
      }
      else if ( pWav->container == drwav_container_rf64 )
      {
        if ( pWav->onSeek(pWav->pUserData, 20, DRWAV_SEEK_SET) )
        {
          riffChunkSize_1 = drwav__riff_chunk_size_rf64(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount);
          drwav__write_u64ne_to_le(pWav, riffChunkSize_1);
        }
        if ( pWav->onSeek(pWav->pUserData, 28, DRWAV_SEEK_SET) )
        {
          dataChunkSize_1 = drwav__data_chunk_size_rf64(pWav->dataChunkDataSize);
          drwav__write_u64ne_to_le(pWav, dataChunkSize_1);
        }
      }
    }
    else
    {
      if ( pWav->onSeek(pWav->pUserData, 4, DRWAV_SEEK_SET) )
      {
        riffChunkSize = drwav__riff_chunk_size_riff(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount);
        drwav__write_u32ne_to_le(pWav, riffChunkSize);
      }
      if ( pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 4, DRWAV_SEEK_SET) )
      {
        dataChunkSize = drwav__data_chunk_size_riff(pWav->dataChunkDataSize);
        drwav__write_u32ne_to_le(pWav, dataChunkSize);
      }
    }
  }
}