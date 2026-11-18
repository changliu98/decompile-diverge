int __cdecl parse_speex_extradata(AVCodecContext *avctx, const uint8_t *extradata, int extradata_size)
{
    SpeexContext *s = (SpeexContext *)avctx->priv_data;
    const uint8_t *buf = (const uint8_t *)av_strnstr((const char *)extradata, "Speex   ", extradata_size);
    
    if (!buf)
        return AVERROR_INVALIDDATA;

    // Skip the "Speex   " string and 20 bytes of header to reach the version_id
    buf += 28;

    s->version_id = bytestream_get_le32(&buf);
    
    // Skip 4 bytes (likely header_size or reserved)
    buf += 4;
    
    s->rate = bytestream_get_le32(&buf);
    if (s->rate <= 0)
        return AVERROR_INVALIDDATA;

    s->mode = bytestream_get_le32(&buf);
    if (s->mode >= 3u)
        return AVERROR_INVALIDDATA;

    s->bitstream_version = bytestream_get_le32(&buf);
    if (s->bitstream_version != 4)
        return AVERROR_INVALIDDATA;

    s->nb_channels = bytestream_get_le32(&buf);
    if (s->nb_channels <= 0 || s->nb_channels > 2)
        return AVERROR_INVALIDDATA;

    s->bitrate = bytestream_get_le32(&buf);
    
    s->frame_size = bytestream_get_le32(&buf);
    // Validate minimum frame size based on mode (160 for narrowband, 320 for wideband)
    if (s->frame_size < 160 << (s->mode > 0))
        return AVERROR_INVALIDDATA;
    
    // Double the frame size if mode > 0
    s->frame_size *= (s->mode > 0) + 1;

    s->vbr = bytestream_get_le32(&buf);
    
    s->frames_per_packet = bytestream_get_le32(&buf);
    // Prevent integer overflow and enforce reasonable limits
    if (s->frames_per_packet <= 0 || 
        s->frames_per_packet > 64 || 
        s->frames_per_packet >= 0x7FFFFFFF / s->nb_channels / s->frame_size)
    {
        return AVERROR_INVALIDDATA;
    }

    s->extra_headers = bytestream_get_le32(&buf);
    
    return 0;
}