int parse_video_info(AVIOContext *pb, AVStream **st_ptr) {
    unsigned int esize;
    unsigned int bi_size;
    int extradata_size;
    int ret;
    unsigned int tag;

    // Read width and height (32-bit little-endian) into AVCodecParameters
    (*st_ptr)->codecpar->width = avio_rl32(pb);
    (*st_ptr)->codecpar->height = avio_rl32(pb);

    // Skip 1 byte
    avio_skip(pb, 1);

    // Read 16-bit tag
    tag = avio_rl16(pb);

    // Parse BMP header and get codec tag
    bi_size = ff_get_bmp_header(pb, *st_ptr, &esize);
    (*st_ptr)->codecpar->bits_per_coded_sample = bi_size;
    (*st_ptr)->codecpar->codec_id = ff_codec_get_id(ff_codec_bmp_tags, bi_size);

    // Determine the maximum between the read tag and esize
    if (tag > esize) {
        extradata_size = tag;
    } else {
        extradata_size = esize;
    }

    // If extradata size is strictly greater than 40 (0x28)
    if (extradata_size > 40) {
        (*st_ptr)->codecpar->extradata_size = extradata_size - 40;
        
        // Allocate extradata buffer with 64 bytes of padding (AV_INPUT_BUFFER_PADDING_SIZE)
        (*st_ptr)->codecpar->extradata = av_malloc((*st_ptr)->codecpar->extradata_size + 64);
        
        if (!(*st_ptr)->codecpar->extradata) {
            (*st_ptr)->codecpar->extradata_size = 0;
            return -12; // AVERROR(ENOMEM)
        }
        
        // Zero out the 64 bytes of padding at the end of the allocated buffer
        memset((*st_ptr)->codecpar->extradata + (*st_ptr)->codecpar->extradata_size, 0, 64);
        
        // Read the remaining extradata from the stream
        ret = avio_read(pb, (*st_ptr)->codecpar->extradata, (*st_ptr)->codecpar->extradata_size);
        if (ret < 0) {
            return ret;
        }
    }

    return 0;
}