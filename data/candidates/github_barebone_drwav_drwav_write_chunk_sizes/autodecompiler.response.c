void drwav_write_chunk_sizes(drwav* pWav)
{
    if (pWav->onWrite == NULL || pWav->isWritingOnRead) {
        return;
    }

    if (pWav->container == 0x0000) {

        if (pWav->onWrite(pWav->pUserData, sizeof(drwav_uint32), 0, &pWav->dataChunkDataSize) != 0) {
            drwav_uint32 riffChunkSize = drwav__riff_chunk_size_riff(pWav->dataChunkDataSize, pWav->metadata.dataChunk.pData, pWav->metadata.dataChunk.dataSize);
            drwav__write_u32ne_to_le(&pWav->dataChunkDataSize, riffChunkSize);
        }

        if (pWav->onWrite(pWav->pUserData, pWav->dataChunkDataSizeOffset - sizeof(drwav_uint32), 0, &pWav->dataChunkDataSize) != 0) {
            drwav_uint32 dataChunkSize = drwav__data_chunk_size_riff(pWav->dataChunkDataSize);
            drwav__write_u32ne_to_le(&pWav->dataChunkDataSize, dataChunkSize);
        }
    } else if (pWav->container == 0x0002) {

        if (pWav->onWrite(pWav->pUserData, sizeof(drwav_uint64), 0, &pWav->dataChunkDataSize) != 0) {
            drwav_uint64 riffChunkSize = drwav__riff_chunk_size_w64(pWav->dataChunkDataSize);
            drwav__write_u64ne_to_le(&pWav->dataChunkDataSize, riffChunkSize);
        }

        if (pWav->onWrite(pWav->pUserData, pWav->dataChunkDataSizeOffset - sizeof(drwav_uint64), 0, &pWav->dataChunkDataSize) != 0) {
            drwav_uint64 dataChunkSize = drwav__data_chunk_size_w64(pWav->dataChunkDataSize);
            drwav__write_u64ne_to_le(&pWav->dataChunkDataSize, dataChunkSize);
        }
    } else if (pWav->container == 0x0003) {

        drwav_uint64 ds64BodyPos = 20 + sizeof(drwav_uint64)*2 + sizeof(drwav_uint32)*2 + sizeof(drwav_uint64)*2;

        if (pWav->onWrite(pWav->pUserData, ds64BodyPos + 0, 0, &pWav->dataChunkDataSize) != 0) {
            drwav_uint64 riffChunkSize = drwav__riff_chunk_size_rf64(pWav->dataChunkDataSize, pWav->metadata.dataChunk.pData, pWav->metadata.dataChunk.dataSize);
            drwav__write_u64ne_to_le(&pWav->dataChunkDataSize, riffChunkSize);
        }

        if (pWav->onWrite(pWav->pUserData, ds64BodyPos + sizeof(drwav_uint64), 0, &pWav->dataChunkDataSize) != 0) {
            drwav_uint64 dataChunkSize = drwav__data_chunk_size_rf64(pWav->dataChunkDataSize);
            drwav__write_u64ne_to_le(&pWav->dataChunkDataSize, dataChunkSize);
        }
    }
}