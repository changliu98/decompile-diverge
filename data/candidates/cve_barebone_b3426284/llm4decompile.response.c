int parse_video_info(AVIOContext *pb, AVStream *st)
{
    int ret;
    uint32_t size_bmp, size_asf;

    st->codecpar->width  = avio_rl32(pb);
    st->codecpar->height = avio_rl32(pb);

    avio_skip(pb, 1);
    size_asf = avio_rl16(pb);

    st->codecpar->codec_tag = ff_get_bmp_header(pb, st, &size_bmp);
    st->codecpar->codec_id = ff_codec_get_id(ff_codec_bmp_tags, st->codecpar->codec_tag);

    if (size_bmp < size_asf)
        size_bmp = size_asf;

    if (size_bmp > 40) {
        st->codecpar->extradata_size = size_bmp - 40;
        st->codecpar->extradata = av_malloc(st->codecpar->extradata_size + 64);
        if (!st->codecpar->extradata) {
            st->codecpar->extradata_size = 0;
            return -12;
        }
        memset(st->codecpar->extradata + st->codecpar->extradata_size, 0, 64);
        ret = avio_read(pb, st->codecpar->extradata, st->codecpar->extradata_size);
        if (ret < 0)
            return ret;
    }

    return 0;
}