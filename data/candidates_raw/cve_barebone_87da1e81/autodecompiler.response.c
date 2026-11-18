__attribute__((used)) static int avr_read_header_old(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVStream *vst, *ast;
    AvrData *avr = s->priv_data;
    int ret, w, h, fps, flags, tag, fsize, freq, channels;
    int64_t rate;
    int64_t start_time, duration;
    int64_t last_pos;
    int64_t last_size;
    int64t avr_read_probe_old(const AVProbeData *p)
{
    int score = 0;
    int vsize, asize;
    int fps, flags;
    int64_t pos;

    if (avio_rl32(p->pb) != MKTAG('A','X','E','D'))
        return 0;

    flags = avio_r8(p->pb);
    avr->frame_size = avio_rb16(p->pb);
    if (!avr->frame_size) {
        av_log(NULL, AV_LOG_ERROR, "File contains no frames ???\n");
        return AVPROBE_SCORE_RETRY;
    }

    fps = avio_rb32(p->pb);
    if (fps > 0) {
        avr->fps_den = 1000;
        avr->fps_num = fps;
    } else if (fps < 0 && fps > INT_MIN + 1) {
        avr->fps_den = 100000;
        avr->fps_num = -fps;
    } else {
        avr->fps_den = 10;
        avr->fps_num = 1;
    }

    while (score < 16) {
        vsize = avio_rb16(pb);
        hsize = avio_rb16(pb);
        avr->video_size = 0;
        vst = avformat_new_stream(s, NULL);
        if (!vst)
            return AVPROBE_SCORE_RETRY;
        if (avio_rl32(pb) == MKTAG('W','A','V','E')) {
            avr->video_size = 1;
            size = avio_rb32(pb);
            avr->video_end = avio_tell(pb) + size;
            x2realloc(pb, 16);
            fsize = avio_rl32(pb);
            ast = avformat_new_stream(s, NULL);
            if (!ast)
                return AVPROBE_SCORE_RETRY;
            ret = ff_get_wav_header(s, pb, ast->codecpar, fsize, 0);
            if (ret < 0)
                return ret;
            if (ast->codecpar->sample_rate > 0)
                avpriv_set_pts_info(ast, 64, 1, ast->codecpar->sample_rate);
        }
        while ((pos = avio_tell(pb)) < avr->video_end && !avio_feof(pb))
            if ((tag = avio_rl32(pb)) != MKTAG('d','a','t','a'))
                x2realloc(pb, fsize);
        avr->video_frames = (fsize + avr->frame_size - 1) / avr->frame_size;
        if (ast->codecpar->block_align) {
            if (avr->video_frames > (INT_MAX - ast->codecpar->block_align + 1) / ast->codecpar->block_align)
                return AVPROBE_SCORE_RETRY;
            avr->video_frames = (avr->video_frames + ast->codecpar->block_align - 1) / ast->codecpar->block_align * ast->codecpar->block_align;
        }
        avr->video_size = fsize;
        avr->video_start = avio_tell(pb);
        avio_seek(pb, avr->video_end, 0);
    }

    vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    vst->codecpar->codec_id = AV_CODEC_ID_RLE;
    vst->codecpar->width = w;
    vst->codecpar->height = h;
    av_reduce(&avr->fps_num, &avr->fps_den, avr->fps_num, avr->fps_den, INT_MAX);
    avpriv_set_pts_info(vst, 33, avr->fps_num, avr->fps_den);
    if ((flags & 0xc0) != 0)
        vst->codecpar->height >>= 1;
    avr->audio = !!(flags & 0x40);
    avr->video_end = avio_tell(pb);

    s->start_time = 0;
    s->duration = av_rescale(avr->frame_size, 1000000LL, avr->fps_den);
    av_log(s, AV_LOG_DEBUG, "%d frame(s)\n", avr->frame_size);

    return score;
}