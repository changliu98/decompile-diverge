int __cdecl jpegxl_anim_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    JXLAnimDemuxContext *ctx = (JXLAnimDemuxContext *)s->priv_data;
    AVIOContext *pb = s->pb;
    
    size_t offset = 0LL;
    __int64 size = avio_size(pb);
    
    // Handle invalid or unknown file sizes
    if (size < 0)
        return size;
    if (!size)
        size = 4096LL;
        
    // Ensure the packet can hold the initial buffer if it exists
    if (ctx->initial && size < ctx->initial->size)
        size = ctx->initial->size;
        
    // Allocate the packet
    int ret = av_new_packet(pkt, size);
    if (ret < 0)
        return ret;
        
    // Copy the initial buffer data into the packet if present
    if (ctx->initial)
    {
        offset = ctx->initial->size;
        memcpy(pkt->data, ctx->initial->data, offset);
        av_buffer_unref(&ctx->initial);
    }
    
    // Read the remaining data from the I/O context
    int bytes_read = avio_read(pb, &pkt->data[offset], size - offset);
    if (bytes_read < 0)
        return bytes_read;
        
    // Adjust packet size if EOF was reached early
    if (bytes_read < size - offset)
        pkt->size = offset + bytes_read;
        
    return 0;
}