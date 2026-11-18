void drwav_write_chunk_sizes(struct drwav *pWav) {
    if (pWav->onWrite == NULL || pWav->isSequentialWrite != 0) {
        return;
    }

    if (pWav->container == 0) { // RIFF
        if (pWav->onWrite(pWav->pUserData, 4, 0) != 0) {
            drwav__write_or_count_u32ne_to_le(pWav, pWav->dataChunkDataSize);
        }
        if (pWav->onWrite(pWav->pUserData, pWav->chunkSize - 4, 0) != 0) {
            drwav__write_or_count_u32ne_to_le(pWav, pWav->chunkSize);
        }
    } else if (pWav->container == 2) { // W64
        if (pWav->onWrite(pWav->pUserData, 16, 0) != 0) {
            drwav__write_or_count_u64ne_to_le(pWav, pWav->dataChunkDataSize);
        }
        if (pWav->onWrite(pWav->pUserData, pWav->chunkSize - 8, 0) != 0) {
            drwav__write_or_count_u64ne_to_le(pWav, pWav->chunkSize);
        }
    } else if (pWav->container == 3) { // RF64
        uint32_t chunkSize = 20;
        if (pWav->onWrite(pWav->pUserData, chunkSize + 0, 0) != 0) {
            drwav__write_or_count_u32ne_to_le(pWav, pWav->dataChunkDataSize);
        }
        if (pWav->onWrite(pWav->pUserData, chunkSize + 8, 0) != 0) {
            drwav__write_or_count_u64ne_to_le(pWav, pWav->chunkSize);
        }
    }
}