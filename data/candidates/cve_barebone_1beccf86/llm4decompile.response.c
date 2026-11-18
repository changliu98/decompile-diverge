int FileSwfDecompression(const uint8_t *buffer, const unsigned buffer_len,
        DetectEngineThreadCtx *det_ctx, InspectionBuffer *out_buffer,
        const int swf_type, const unsigned decompress_depth,
        const unsigned compress_depth)
{
    unsigned offset = 0;
    unsigned compressed_data_len;
    unsigned decompressed_data_len;
    unsigned decompressed_swf_len;
    unsigned swf_version;
    int compression_type;

    compression_type = FileIsSwfFile(buffer, buffer_len);
    if (compression_type == 1)
        return 0;

    if (compression_type == 2)
        offset = 8;
    else if (compression_type == 3)
        offset = 17;

    if (offset >= buffer_len) {
        DetectEngineSetEvent(det_ctx, 0x01);
        return 0;
    }

    if (compress_depth == 0 || compress_depth > buffer_len - offset)
        compressed_data_len = buffer_len - offset;
    else
        compressed_data_len = compress_depth;

    swf_version = FileGetSwfVersion(buffer, buffer_len);

    if (compression_type == 2 && swf_version < 6) {
        DetectEngineSetEvent(det_ctx, 0x02);
        return 0;
    }

    if (compression_type == 3 && swf_version < 13) {
        DetectEngineSetEvent(det_ctx, 0x02);
        return 0;
    }

    decompressed_swf_len = FileGetSwfDecompressedLen(buffer, buffer_len);
    if (decompressed_swf_len == 0)
        decompressed_swf_len = 2920;

    if (decompress_depth == 0)
        decompressed_data_len = decompressed_swf_len;
    else
        decompressed_data_len = decompress_depth;

    decompressed_data_len += 8;

    SCInspectionBufferCheckAndExpand(out_buffer, decompressed_data_len);
    if (out_buffer->size < decompressed_data_len) {
        DetectEngineSetEvent(det_ctx, 0x03);
        return 0;
    }

    out_buffer->len = decompressed_data_len;

    out_buffer->buf[0] = 'F';
    out_buffer->buf[1] = 'W';
    out_buffer->buf[2] = 'S';
    out_buffer->buf[3] = swf_version;
    *(uint32_t *)(&out_buffer->buf[4]) = decompressed_swf_len;

    memset(&out_buffer->buf[8], 0, decompressed_data_len - 8);

    if ((swf_type == 1 || swf_type == 3) && compression_type == 2) {
        if (!FileSwfZlibDecompression(det_ctx, &buffer[offset],
                compressed_data_len, &out_buffer->buf[8],
                out_buffer->len - 8))
            return 0;
    } else if ((swf_type == 2 || swf_type == 3) && compression_type == 3) {
        uint8_t lzma_compressed_data[398];

        *(uint32_t *)(&lzma_compressed_data[0]) = *(uint32_t *)(&buffer[12]);
        lzma_compressed_data[4] = buffer[16];
        memset(&lzma_compressed_data[5], 0xff, 8);
        memcpy(&lzma_compressed_data[13], &buffer[offset],
                compressed_data_len - 13);
        compressed_data_len += 13;

        if (!FileSwfLzmaDecompression(det_ctx, lzma_compressed_data,
                compressed_data_len