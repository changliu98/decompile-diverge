static int parse_video_info(struct AVIOContext *pb, struct AVStream *st)
{
    struct AVIOContext *pb_asf = pb;
    struct AVStream *st_asf = st;
    st->codecpar->width = read_le_int(pb_asf);
    st->codecpar->height = read_le_int(pb_asf);
    read_le_int(pb_asf);
    unsigned short size_asf = read_le_short(pb_asf);
    unsigned int size_bmp = read_le_int(pb_asf);
    int tag = read_le_int(pb_asf, st_asf, &size_bmp);
    st->codecpar->codec_tag = tag;
    st->codecpar->codec_id = get_codec_by_tag(&ff_codec_bmp_tags, tag);
    if (size_asf > size_bmp)
        size_bmp = size_asf;
    else
        size_bmp = size_bmp;
    if (size_bmp > 40) {
        st->codecpar->extradata_size = size_bmp - 40;
        st->codecpar->extradata = (unsigned char *)av_mallocz(size_bmp - 40 + sizeof(AVCodecParser));
        if (!st->codecpar->extradata) {
            st->codecpar->extradata_size = 0;
            return -12;
        }
        memset(st->codecpar->extradata + st->codecpar->extradata_size, 0, sizeof(AVCodecParser));
        int ret = read_le_int(pb, st->codecpar->extradata, st->codecpar->extradata_size);
        if (ret < 0)
            return ret;
    }
    return 0;
}