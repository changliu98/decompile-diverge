static int FileSwfDecompression(unsigned char *buffer, unsigned int buffer_len,
                                DetectEngineState *s, InspectBuffer *output,
                                int swf_type, unsigned int decompress_depth,
                                unsigned int compress_depth)
{
    int ret = 0;
    unsigned int offset;
    unsigned int compressed_data_len;
    unsigned int decompressed_data_len;
    unsigned int decompressed_swf_len;
    unsigned int swf_version;
    unsigned int swf_compression_type;
    unsigned int max_decompressed_data_len;

    unsigned int offset_to_copy = 0;

    swf_compression_type = FileIsSwfFile(buffer, buffer_len);

    if (swf_compression_type == 1) {

        offset = 0;
    } else {
        offset = 0;

        if (swf_compression_type == 2) {
            offset = 8;
        } else if (swf_compression_type == 3) {
            offset = 17;
        }

        if (buffer_len <= offset) {
            DetectEngineSetEvent(s, 1);
            ret = 0;
            goto end;
        }
        compressed_data_len = 0;

        if ((compress_depth > 0) && (compress_depth <= (buffer_len - offset)))
            compressed_data_len = compress_depth;
        else
            compressed_data_len = buffer_len - offset;

        swf_version = FileGetSwfVersion(buffer, buffer_len);

        if ((swf_compression_type == 2) && (swf_version < 7)) {
            DetectEngineSetEvent(s, 2);
            ret = 0;
            goto end;
        }

        if ((swf_compression_type == 3) && (swf_version < 14)) {
            DetectEngineSetEvent(s, 2);
            ret = 0;
            goto end;
        }

        decompressed_swf_len = FileGetSwfDecompressedLen(buffer, buffer_len);

        if (decompressed_swf_len == 0)
            decompressed_swf_len = 2920;

        if (decompress_depth == 0)
            max_decompressed_data_len = decompressed_swf_len;
        else
            max_decompressed_data_len = decompress_depth;

        decompressed_data_len = max_decompressed_data_len;

        decompressed_data_len += 8;

        SCInspectionBufferCheckAndExpand(output, decompressed_data_len);

        if (output->size < decompressed_data_len) {
            DetectEngineSetEvent(s, 3);
            ret = 0;
            goto end;
        }

        output->len = decompressed_data_len;

        output->ptr[0] = 'F';
        output->ptr[1] = 'W';
        output->ptr[2] = 'S';
        output->ptr[3] = swf_version;
        output->ptr[4] = (unsigned char)(decompressed_swf_len & 0xff);
        output->ptr[5] = (unsigned char)((decompressed_swf_len >> 8) & 0xff);
        output->ptr[6] = (unsigned char)((decompressed_swf_len >> 16) & 0xff);
        output->ptr[7] = (unsigned char)((decompressed_swf_len >> 24) & 0xff);

        memset(&output->ptr[8], 0, (decompressed_data_len - 8));

        if ((swf_type == 1 || swf_type == 3) &&
                swf_compression_type == 2) {
            ret = FileSwfZlibDecompression(s, &buffer[offset],
                                           compressed_data_len,
                                           &output->ptr[8],
                                           output->len - 8);
            if (!ret)
                goto error;
        } else if ((swf_type == 2 || swf_type == 3) &&
                   swf_compression_type == 3) {
            unsigned int lzma_header_size = 13 + compressed_data_len;
            unsigned char lzma_header[lzma_header_size];
            unsigned int lzma_ret;

            lzma_header[0] = buffer[3];
            lzma_header[1] = buffer[4];
            lzma_header[2] = buffer[5];
            lzma_header[3] = buffer[6];

            lzma_header[4] = buffer[7];

            lzma_header[5] = buffer[8];
            lzma_header[6] = buffer[9];
            lzma_header[7] = buffer[10];
            lzma_header[8] = buffer[11];

            lzma_header[9] = buffer[12];
            lzma_header[10] = buffer[13];
            lzma_header[11] = buffer[14];
            lzma_header[12] = buffer[15];

            memset(&lzma_header[13], 0xff, 8);

            memcpy(&lzma_header[13], &buffer[offset], lzma_header_size - 13);

            ret = FileSwfLzmaDecompression(s, lzma_header, lzma_header_size,
                                            &output->ptr[8],
                                            output->len - 8);
            if (!ret)
                lzma_ret = 2;
            else
                lzma_ret = 0;

            if (lzma_ret != 0)
                goto error;
        } else {
error:
            ret = 0;
            goto end;
        }

        output->inspect = output->ptr;
        output->inspect_len = output->len;

        ret = 1;
end:
        return ret;
}