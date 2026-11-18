static void drwav_write_chunk_sizes(drwav* pWav) {
  if (pWav->onChunk == NULL || pWav->isContainerFormat) {
    return;
  }
  if (pWav->container == drwav_container_w64) {
    if (pWav->onChunk(pWav->pUserData, 16, drwav_chunk_type_riff)) {
      drwav_uint64 chunkSize = drwav__riff_chunk_size_w64(pWav->totalSampleData);
      drwav__write_u64ne_to_le(pWav, chunkSize);
    }
    if (pWav->onChunk(pWav->pUserData, pWav->bytesWritten - 8,
                      drwav_chunk_type_riff)) {
      drwav_uint64 chunkSize = drwav__data_chunk_size_w64(pWav->totalSampleData);
      drwav__write_u64ne_to_le(pWav, chunkSize);
    }
  } else if (pWav->container == drwav_container_rf64) {
    if (pWav->onChunk(pWav->pUserData, 20, drwav_chunk_type_riff)) {
      drwav_uint64 chunkSize = drwav__riff_chunk_size_rf64(
          pWav->totalSampleData, pWav->sampleRate, pWav->channels);
      drwav__write_u64ne_to_le(pWav, chunkSize);
    }
    if (pWav->onChunk(pWav->pUserData, 28, drwav_chunk_type_riff)) {
      drwav_uint64 chunkSize = drwav__data_chunk_size_rf64(pWav->totalSampleData);
      drwav__write_u64ne_to_le(pWav, chunkSize);
    }
  } else {
    if (pWav->onChunk(pWav->pUserData, 4, drwav_chunk_type_riff)) {
      drwav_uint32 chunkSize = drwav__riff_chunk_size_riff(
          pWav->totalSampleData, pWav->sampleRate, pWav->channels);
      drwav__write_u32ne_to_le(pWav, chunkSize);
    }
    if (pWav->onChunk(pWav->pUserData, pWav->bytesWritten - 4,
                      drwav_chunk_type_riff)) {
      drwav_uint32 chunkSize = drwav__data_chunk_size_riff(pWav->totalSampleData);
      drwav__write_u32ne_to_le(pWav, chunkSize);
    }
  }
}