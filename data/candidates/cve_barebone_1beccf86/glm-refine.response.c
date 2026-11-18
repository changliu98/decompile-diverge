int __cdecl FileSwfDecompression(
        const uint8_t *buffer,
        uint32_t buffer_len,
        DetectEngineThreadCtx *det_ctx,
        InspectionBuffer *out_buffer,
        int swf_type,
        uint32_t decompress_depth,
        uint32_t compress_depth)
{
    uint8_t *compressed_data;
    uint32_t decompressed_data_len;
    uint32_t decompressed_swf_len;
    uint8_t swf_version;
    uint32_t compressed_data_len;
    uint32_t offset;
    int compression_type;
    int r;
    uint32_t max_decompress_len;

    r = 0;
    compression_type = FileIsSwfFile(buffer, buffer_len);
    
    // If compression_type == 1, the SWF is already uncompressed ('FWS')
    if (compression_type == 1)
        return 0;

    offset = 0;
    if (compression_type == 2)      // CWS (Zlib compressed)
        offset = 8;
    else if (compression_type == 3) // ZWS (LZMA compressed)
        offset = 17;

    if (buffer_len <= offset) {
        DetectEngineSetEvent(det_ctx, 1u);
        return 0;
    }

    // Determine the length of compressed data to read
    compressed_data_len = 0;
    if (compress_depth && compress_depth <= buffer_len - offset)
        compressed_data_len = compress_depth;
    else
        compressed_data_len = buffer_len - offset;

    swf_version = FileGetSwfVersion(buffer, buffer_len);
    
    // Check for invalid SWF version given the compression type
    if ((compression_type == 2 && swf_version < 6u) || 
        (compression_type == 3 && swf_version < 0xDu)) 
    {
        DetectEngineSetEvent(det_ctx, 2u);
        return 0;
    }

    decompressed_swf_len = FileGetSwfDecompressedLen(buffer, buffer_len);
    if (!decompressed_swf_len)
        decompressed_swf_len = 2920; // Default fallback length

    // Determine max decompression length
    if (decompress_depth)
        max_decompress_len = decompress_depth;
    else
        max_decompress_len = decompressed_swf_len;

    decompressed_data_len = max_decompress_len + 8;
    SCInspectionBufferCheckAndExpand(out_buffer, max_decompress_len + 8);

    if (out_buffer->size < max_decompress_len + 8) {
        DetectEngineSetEvent(det_ctx, 3u);
        return 0;
    }

    out_buffer->len = decompressed_data_len;
    
    // Construct the uncompressed SWF header ('FWS')
    out_buffer->buf[0] = 'F'; // 70
    out_buffer->buf[1] = 'W'; // 87
    out_buffer->buf[2] = 'S'; // 83
    out_buffer->buf[3] = swf_version;
    *((uint32_t *)out_buffer->buf + 1) = decompressed_swf_len;
    
    memset(out_buffer->buf + 8, 0, decompressed_data_len - 8);

    // Handle Zlib decompression (CWS)
    if ((swf_type == 1 || swf_type == 3) && compression_type == 2) 
    {
        r = FileSwfZlibDecompression(
                det_ctx,
                buffer + offset,
                compressed_data_len,
                out_buffer->buf + 8,
                out_buffer->len - 8);
                
        if (r) {
            out_buffer->inspect = out_buffer->buf;
            out_buffer->inspect_len = out_buffer->len;
            return 1;
        }
    }
    // Handle LZMA decompression (ZWS)
    else if ((swf_type == 2 || swf_type == 3) && compression_type == 3) 
    {
        compressed_data_len += 13; // Extend length to include reconstructed LZMA header
        
        // Variable Length Array (VLA) allocation
        uint8_t vla_buf[compressed_data_len]; 
        
        // Reconstruct LZMA header properties
        *(uint32_t *)vla_buf = *((uint32_t *)buffer + 3); // Copy LZMA properties from SWF header
        vla_buf[4] = buffer[16];                          // Copy 5th byte of properties
        memset(vla_buf + 5, 0xFF, 8);                     // Fill uncompressed size with 0xFFFFFFFF (unknown)
        memcpy(vla_buf + 13, buffer + offset, compressed_data_len - 13); // Copy compressed payload
        
        r = FileSwfLzmaDecompression(
                det_ctx,
                vla_buf,
                compressed_data_len,
                out_buffer->buf + 8,
                out_buffer->len - 8);
                
        // Original assembly logic: `if (!(r ? 0 : 2))` evaluates to true if r != 0
        if (r) {
            out_buffer->inspect = out_buffer->buf;
            out_buffer->inspect_len = out_buffer->len;
            return 1;
        }
    }

    return 0;
}