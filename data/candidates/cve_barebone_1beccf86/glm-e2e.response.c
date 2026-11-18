int FileSwfDecompression(SwfFile *file, int file_size, void *detect_engine, InspectionBuffer *buffer, int mode, int decompressed_len) {
    int ret = 0;
    int swf_type = FileIsSwfFile(file, file_size);
    
    if (swf_type == 1) {
        return 0;
    }

    int header_len = 0;
    if (swf_type == 2) {
        header_len = 8;
    } else if (swf_type == 3) {
        header_len = 17;
    }

    if (file_size <= header_len) {
        DetectEngineSetEvent(detect_engine, 1);
        return 0;
    }

    int len = 0;
    if (decompressed_len > 0 && (unsigned int)decompressed_len <= (unsigned int)(file_size - header_len)) {
        len = decompressed_len;
    } else {
        len = file_size - header_len;
    }

    unsigned char version = (unsigned char)FileGetSwfVersion(file, file_size);

    if (swf_type == 2 && version < 6) {
        DetectEngineSetEvent(detect_engine, 2);
        return 0;
    }

    if (swf_type == 3 && version < 13) {
        DetectEngineSetEvent(detect_engine, 2);
        return 0;
    }

    int decompressed_size = FileGetSwfDecompressedLen(file, file_size);
    if (decompressed_size == 0) {
        decompressed_size = 2920; // 0xb68
    }

    int expected_size = (decompressed_len == 0) ? decompressed_size : decompressed_len;
    expected_size += 8;

    SCInspectionBufferCheckAndExpand(buffer, expected_size);

    if (buffer->buf_size < (unsigned int)expected_size) {
        DetectEngineSetEvent(detect_engine, 3);
        return 0;
    }

    buffer->data_len = expected_size;
    buffer->data[0] = 'F';
    buffer->data[1] = 'W';
    buffer->data[2] = 'S';
    buffer->data[3] = version;
    *(int *)(buffer->data + 4) = decompressed_size;

    memset(buffer->data + 8, 0, expected_size - 8);

    if ((mode == 1 || mode == 3) && swf_type == 2) {
        ret = FileSwfZlibDecompression(detect_engine, file->data + header_len, len, buffer->data + 8, buffer->data_len - 8);
        if (ret == 0) {
            goto success;
        }
    } else if ((mode == 2 || mode == 3) && swf_type == 3) {
        len += 13;
        
        // Variable Length Array (VLA) dynamically allocated on the stack
        char vla_buffer[len];
        
        // Copy LZMA header properties
        *(int *)vla_buffer = *(int *)(file->data + 12);
        vla_buffer[4] = *(unsigned char *)(file->data + 16);
        
        // Fill LZMA dummy size bytes
        memset(vla_buffer + 5, 0xff, 8);
        
        // Copy compressed data
        memcpy(vla_buffer + 13, file->data + header_len, len - 13);
        
        ret = FileSwfLzmaDecompression(detect_engine, vla_buffer, len, buffer->data + 8, buffer->data_len - 8);
        
        if (ret != 0) {
            goto success;
        }
    } else {
        goto success;
    }

success:
    buffer->buf = buffer->data;
    buffer->size = buffer->data_len;
    return 1;
}