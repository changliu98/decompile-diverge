void drwav_write_chunk_sizes(struct DrWAV *pWav)
{
  if (pWav->onSeek && !pWav->isSequentialWrite)
  {
    if (pWav->container == drwav_container_none)
    {
      if (pWav->onSeek(pWav->pUserData, 4, DRWAV_SEEK_SET))
      {
        unsigned int chunkSize = drwav_write_chunk_size(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount);
        drwav_write_chunk_id(pWav, chunkSize);
      }
      if (pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 4, DRWAV_SEEK_SET))
      {
        unsigned int dataSize = drwav_write_data_size(pWav->dataChunkDataSize);
        drwav_write_chunk_id(pWav, dataSize);
      }
    }
    else if (pWav->container == drwav_container_w64)
    {
      if (pWav->onSeek(pWav->pUserData, 16, DRWAV_SEEK_SET))
      {
        unsigned int chunkSize = drwav_write_chunk_size_w64(pWav->dataChunkDataSize);
        drwav_write_chunk_id(pWav, chunkSize);
      }
      if (pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 8, DRWAV_SEEK_SET))
      {
        unsigned int dataSize = drwav_write_data_size_w64(pWav->dataChunkDataSize);
        drwav_write_chunk_id(pWav, dataSize);
      }
    }
    else if (pWav->container == drwav_container_rf64)
    {
      if (pWav->onSeek(pWav->pUserData, 20, DRWAV_SEEK_SET))
      {
        unsigned int chunkSize = drwav_write_chunk_size_rf64(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount);
        drwav_write_chunk_id(pWav, chunkSize);
      }
      if (pWav->onSeek(pWav->pUserData, 28, DRWAV_SEEK_SET))
      {
        unsigned int dataSize = drwav_write_data_size_rf64(pWav->dataChunkDataSize);
        drwav_write_chunk_id(pWav, dataSize);
      }
    }
  }
}