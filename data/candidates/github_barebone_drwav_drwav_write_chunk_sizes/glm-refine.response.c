void __cdecl drwav_write_chunk_sizes(drwav *pWav)
{
    // Guard clause: only update chunk sizes if seeking is allowed and we're not in sequential write mode
    if (!pWav->onSeek || pWav->isSequentialWrite)
    {
        return;
    }

    switch (pWav->container)
    {
        case drwav_container_w64:
            if (pWav->onSeek(pWav->pUserData, 16, DRWAV_SEEK_SET))
            {
                drwav__write_u64ne_to_le(pWav, drwav__riff_chunk_size_w64(pWav->dataChunkDataSize));
            }
            if (pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 8, DRWAV_SEEK_SET))
            {
                drwav__write_u64ne_to_le(pWav, drwav__data_chunk_size_w64(pWav->dataChunkDataSize));
            }
            break;

        case drwav_container_rf64:
            if (pWav->onSeek(pWav->pUserData, 20, DRWAV_SEEK_SET))
            {
                drwav__write_u64ne_to_le(pWav, drwav__riff_chunk_size_rf64(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount));
            }
            if (pWav->onSeek(pWav->pUserData, 28, DRWAV_SEEK_SET))
            {
                drwav__write_u64ne_to_le(pWav, drwav__data_chunk_size_rf64(pWav->dataChunkDataSize));
            }
            break;

        case 0: // drwav_container_riff (implied by original else branch)
        default:
            if (pWav->onSeek(pWav->pUserData, 4, DRWAV_SEEK_SET))
            {
                drwav__write_u32ne_to_le(pWav, drwav__riff_chunk_size_riff(pWav->dataChunkDataSize, pWav->pMetadata, pWav->metadataCount));
            }
            if (pWav->onSeek(pWav->pUserData, pWav->dataChunkDataPos - 4, DRWAV_SEEK_SET))
            {
                drwav__write_u32ne_to_le(pWav, drwav__data_chunk_size_riff(pWav->dataChunkDataSize));
            }
            break;
    }
}