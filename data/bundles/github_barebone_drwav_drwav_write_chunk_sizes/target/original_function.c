DRWAV_PRIVATE void drwav_write_chunk_sizes(drwav* pWav)
{
    /*
    When using sequential mode, these will have been filled in at initialization time. We only need
    to do this when using non-sequential mode.
    */
    if (pWav->onSeek != NULL && !pWav->isSequentialWrite) {
        if (pWav->container == drwav_container_riff) {
            /* The "RIFF" chunk size. */
            if (pWav->onSeek(pWav->pUserData, 4, DRWAV_SEEK_SET)) {
                drwav_uint32 riffChunkSize = drwav__riff_chunk_size_riff(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount);
                drwav__write_u32ne_to_le(pWav, riffChunkSize);
            }

            /* The "data" chunk size. */
            if (pWav->onSeek(pWav->pUserData, (int)pWav->dataChunkDataPos - 4, DRWAV_SEEK_SET)) {
                drwav_uint32 dataChunkSize = drwav__data_chunk_size_riff(pWav->dataChunkDataSize);
                drwav__write_u32ne_to_le(pWav, dataChunkSize);
            }
        } else if (pWav->container == drwav_container_w64) {
            /* The "RIFF" chunk size. */
            if (pWav->onSeek(pWav->pUserData, 16, DRWAV_SEEK_SET)) {
                drwav_uint64 riffChunkSize = drwav__riff_chunk_size_w64(pWav->dataChunkDataSize);
                drwav__write_u64ne_to_le(pWav, riffChunkSize);
            }

            /* The "data" chunk size. */
            if (pWav->onSeek(pWav->pUserData, (int)pWav->dataChunkDataPos - 8, DRWAV_SEEK_SET)) {
                drwav_uint64 dataChunkSize = drwav__data_chunk_size_w64(pWav->dataChunkDataSize);
                drwav__write_u64ne_to_le(pWav, dataChunkSize);
            }
        } else if (pWav->container == drwav_container_rf64) {
            /* We only need to update the ds64 chunk. The "RIFF" and "data" chunks always have their sizes set to 0xFFFFFFFF for RF64. */
            int ds64BodyPos = 12 + 8;

            /* The "RIFF" chunk size. */
            if (pWav->onSeek(pWav->pUserData, ds64BodyPos + 0, DRWAV_SEEK_SET)) {
                drwav_uint64 riffChunkSize = drwav__riff_chunk_size_rf64(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount);
                drwav__write_u64ne_to_le(pWav, riffChunkSize);
            }

            /* The "data" chunk size. */
            if (pWav->onSeek(pWav->pUserData, ds64BodyPos + 8, DRWAV_SEEK_SET)) {
                drwav_uint64 dataChunkSize = drwav__data_chunk_size_rf64(pWav->dataChunkDataSize);
                drwav__write_u64ne_to_le(pWav, dataChunkSize);
            }
        }
    }
}