int __cdecl parse_video_info(AVIOContext *pb, AVStream *st)
{
    uint32_t size_bmp;
    uint16_t size_asf;
    int tag, ret;
    AVCodecID codec_id;
    uint8_t *extradata;
    uint32_t max_size;

    // Read video dimensions
    st->codecpar->width  = avio_rl32(pb);
    st->codecpar->height = avio_rl32(pb);

    // Skip unknown byte and read ASF size
    avio_skip(pb, 1);
    size_asf = avio_rl16(pb);

    // Read BMP header and determine codec tag/id
    tag = ff_get_bmp_header(pb, st, &size_bmp);
    st->codecpar->codec_tag = tag;
    codec_id = ff_codec_get_id(&ff_codec_bmp_tags, tag);
    st->codecpar->codec_id = codec_id;

    // Determine the maximum size between ASF and BMP headers
    max_size = (size_asf > size_bmp) ? size_asf : size_bmp;
    size_bmp = max_size;

    // If the maximum size is less than or equal to 40 (0x28) bytes, no extra data is present
    if (max_size <= 0x28)
        return 0;

    st->codecpar->extradata_size = size_bmp - 40;

    // Allocate extradata buffer with 64 bytes of padding (AV_INPUT_BUFFER_PADDING_SIZE)
    extradata = (uint8_t *)av_malloc(st->codecpar->extradata_size + 64);
    st->codecpar->extradata = extradata;

    if (extradata)
    {
        // Zero out the padding area
        memset(&extradata[st->codecpar->extradata_size], 0, 64);

        // Read the extradata from the stream
        ret = avio_read(pb, extradata, st->codecpar->extradata_size);
        if (ret < 0)
            return ret;

        return 0;
    }

    // Allocation failed (ENOMEM is typically -12)
    st->codecpar->extradata_size = 0;
    return -12;
}