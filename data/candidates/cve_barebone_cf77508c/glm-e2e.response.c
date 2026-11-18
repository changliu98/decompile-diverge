int jpegxl_anim_read_packet(JpegXLAnimDemuxContext *ctx, AVPacket *pkt) {
    AVBufferRef **buf = ctx->buf;
    AVIOContext *pb = ctx->pb;
    int64_t size_64;
    int size;
    int ret;
    int64_t initial_size = 0;
    
    size_64 = avio_size(pb);
    if (size_64 < 0) {
        return (int)size_64;
    }
    
    if (size_64 == 0) {
        size_64 = 0x1000;
    }
    
    if (*buf != NULL) {
        if ((uint64_t)size_64 >= (*buf)->size) {
            size_64 = (*buf)->size;
        }
    }
    
    size = (int)size_64;
    ret = av_new_packet(pkt, size);
    if (ret < 0) {
        return ret;
    }
    
    if (*buf != NULL) {
        initial_size = (*buf)->size;
        memcpy(((AVPacketCompat *)pkt)->data, (*buf)->data, initial_size);
        av_buffer_unref(buf);
    }
    
    ret = avio_read(pb, ((AVPacketCompat *)pkt)->data + initial_size, size - initial_size);
    if (ret < 0) {
        return ret;
    }
    
    if (ret < size - initial_size) {
        ((AVPacketCompat *)pkt)->size = ret + initial_size;
    }
    
    return 0;
}