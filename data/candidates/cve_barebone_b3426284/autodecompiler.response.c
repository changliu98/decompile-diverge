__attribute__((used)) static int parse_video_info(AVIOContext *pb, AVStream *st)
{
    unsigned int size, bmsize;
    int ret;
    unsigned short w;

    /* bitmapinfoheader is 40 bytes, but it can be extended to 64 bytes
     * for BITMAPINFOHEADER2 and BITMAPINFOHEADER3 */
    st->codecpar->extradata_size = size = avio_rl32(pb);
    st->codecpar->bit_rate       = avio_rl32(pb);
    avio_skip(pb, 1);
    w              = avio_rl16(pb);
    st->codecpar->codec_tag  = ff_codec_get_id(&ff_codec_bmp_tags,
                                               bmsize = ff_get_bmp_header(pb, st));
    st->codecpar->codec_id   = ff_codec_bmp_tags.bom[st->codecpar->codec_tag];
    if (w > bmsize)
        bmsize = w;
    if (bmsize > 40) {
        st->codecpar->extradata_size = bmsize - 40;
        st->codecpar->extradata      = av_malloc(64 + st->codecpar->extradata_size);
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