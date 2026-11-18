int dxa_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    DXAContext *c = s->priv_data;
    AVStream *st, *ast;
    int w, h, flags, fps, fsize, tag, den, num;

    tag = avio_rl32(pb);
    if (tag != 0x41584544)
        return -0x41444e49;

    flags = avio_r8(pb);
    c->frames = avio_rb16(pb);
    if (!c->frames) {
        av_log(s, 16, "File contains no frames ???\n");
        return -0x41444e49;
    }

    fps = avio_rb32(pb);
    if (fps > 0) {
        den = 1000;
        num = fps;
    } else if (fps < 0 && fps > -2147483648LL) {
        den = 100000;
        num = -fps;
    } else {
        den = 10;
        num = 1;
    }

    w = avio_rb16(pb);
    h = avio_rb16(pb);

    c->has_sound = 0;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return -12;

    tag = avio_rl32(pb);
    if (tag == 0x45564157) {
        c->has_sound = 1;
        fsize = avio_rb32(pb);
        c->vidpos = avio_tell(pb) + fsize;
        avio_skip(pb, 16);
        fsize = avio_rl32(pb);
        ast = avformat_new_stream(s, NULL);
        if (!ast)
            return -12;
        int err = ff_get_wav_header(s, pb, ast->codecpar, fsize, 0);
        if (err < 0)
            return err;
        if (ast->codecpar->sample_rate > 0)
            avpriv_set_pts_info(ast, 64, 1, ast->codecpar->sample_rate);

        while (avio_tell(pb) < c->vidpos && !avio_feof(pb)) {
            tag = avio_rl32(pb);
            fsize = avio_rl32(pb);
            if (tag == 0x61746164)
                break;
            avio_skip(pb, fsize);
        }

        c->bpc = (fsize + c->frames - 1) / c->frames;
        if (ast->codecpar->block_align) {
            if (c->bpc > 0x80000000 - ast->codecpar->block_align)
                return -0x41444e49;
            c->bpc = (c->bpc + ast->codecpar->block_align - 1) / ast->codecpar->block_align;
            c->bpc *= ast->codecpar->block_align;
        }
        c->bytes_left = fsize;
        c->wavpos = avio_tell(pb);
        avio_seek(pb, c->vidpos, 0);
    }

    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_DXA;
    st->codecpar->width = w;
    st->codecpar->height = h;
    av_reduce(&den, &num, den, num, 0x7FFFFFFF);
    avpriv_set_pts_info(st, 33, num, den);

    if (flags & 0xC0)
        st->codecpar->height >>= 1;

    c->readvid = !c->has_sound;
    c->vidpos = avio_tell(pb);

    s->start_time = 0;
    s->duration = av_rescale(c->frames, 1000000LL * num, den);

    av_log(s, 48, "%d frame(s)\n", c->frames);

    return 0;
}