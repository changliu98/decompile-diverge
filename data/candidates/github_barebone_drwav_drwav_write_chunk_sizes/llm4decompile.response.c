void drwav_write_chunk_sizes(drwav* pWav)
{
    if (pWav->onSeek == NULL || pWav->isSequentialWrite) {
        return;
    }

    if (pWav->container == drwav_container_riff) {
        if (pWav->onSeek(pWav->pUserData, 4, DRWAV_SEEK_SET)) {
            drwav__write_u32ne_to_le(pWav, drwav__riff_chunk_size_riff(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount));
        }

        if (pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 4, DRWAV_SEEK_SET)) {
            drwav__write_u32ne_to_le(pWav, drwav__data_chunk_size_riff(pWav->dataChunkDataSize));
        }
    } else if (pWav->container == drwav_container_w64) {
        if (pWav->onSeek(pWav->pUserData, 16, DRWAV_SEEK_SET)) {
            drwav__write_u64ne_to_le(pWav, drwav__riff_chunk_size_w64(pWav->dataChunkDataSize));
        }

        if (pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 8, DRWAV_SEEK_SET)) {
            drwav__write_u64ne_to_le(pWav, drwav__data_chunk_size_w64(pWav->dataChunkDataSize));
        }
    } else if (pWav->container == drwav_container_rf64) {
        if (pWav->onSeek(pWav->pUserData, 20, DRWAV_SEEK_SET)) {
            drwav__write_u64ne_to_le(pWav, drwav__riff_chunk_size_rf64(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount));
        }

        if (pWav->onSeek(pWav->pUserData, 28, DRWAV_SEEK_SET)) {
            drwav__write_u64ne_to_le(pWav, drwav__data_chunk_size_rf64(pWav->dataChunkDataSize));
        }
    }
}