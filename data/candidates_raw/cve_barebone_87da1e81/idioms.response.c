static int dxa_read_header(struct AVFormatContext *ctx)
{
    struct AVIOContext *pb = ctx->pb;
    struct DXAContext *dxac = ctx->priv_data;
    unsigned int tag;
    int flags;
    int fps; int num; int den;
    int w; int h;
    struct AVStream *st;
    struct AVStream *ast;
    unsigned int ssize; unsigned int fsize;
    tag = avio_rl32(pb);
    if (tag != 0x41565844)
        return -1094995529;
    flags = avio_rl8(pb);
    dxac->frames = avio_rl32(pb);
    if (dxac->frames == 0) {
        av_log(ctx, AV_LOG_ERROR, "File contains no frames ???\n");
        return -1094995529;
    }
    fps = avio_rl32(pb);
    if (fps > 0) {
        den = 1000;
        num = fps;
    } else if (fps < 0 && fps != (-0x7fffffff - 1)) {
        den = 100000;
        num = -fps;
    } else {
        den = 10;
        num = 1;
    }
    w = avio_rl32(pb);
    h = avio_rl32(pb);
    dxac->has_sound = 0;
    st = avformat_new_stream(ctx, ((void *)0));
    if (!st)
        return -12;
    if (avio_rl32(pb) == 0x44525257) {
        dxac->has_sound = 1;
        ssize = avio_rl32(pb);
        dxac->wavpos = avio_rb64(pb) + ssize;
        avio_rb64(pb);
        fsize = avio_rl32(pb);
        ast = avformat_new_stream(ctx, ((void *)0));
        if (!ast)
            return -12;
        if (avio_read(pb, (char *)((void *)0), fsize) < 0)
            return -1094995529;
        if (ast->codecpar->sample_rate > 0)
            av_set_pts_info(ast, AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX, 1, ast->codecpar->sample_rate);
        while (1) {
            unsigned char flag = 0;
            if (avio_rb64(pb) < dxac->wavpos)
                flag = (avio_rl32(pb) != 0);
            if (flag & 1) {
                tag = avio_rl32(pb);
                fsize = avio_rl32(pb);
                if (tag == 0x616d6154)
                    break;
                avio_skip(pb, fsize);
            }
        }
        dxac->bpc = (dxac->frames + fsize - 1) / dxac->frames;
        if (ast->codecpar->block_align > 0) {
            if (dxac->bpc + -1 >= 0x80000000 - ast->codecpar->block_align)
                return -1094995529;
            dxac->bpc = (dxac->bpc + ast->codecpar->block_align - 1) /
                ast->codecpar->block_align * ast->codecpar->block_align;
        }
        dxac->bytes_left = fsize;
        dxac->wavpos = avio_rb64(pb);
        avio_seek(pb, dxac->wavpos, AVIO_SEEK_SET);
    }
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_DXA;
    st->codecpar->width = w;
    st->codecpar->height = h;
    av_gcd(&den, &num, 0x7fffffff);
    av_set_pts_info(st, AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX, num, den);
    if (flags & (0x40 | 0x80))
        st->codecpar->height /= 2;
    dxac->readvid = !dxac->has_sound;
    dxac->vidpos = avio_rb64(pb);
    ctx->start_time = 0;
    ctx->duration = av_rescale_q(dxac->frames, num, den);
    av_log(ctx, AV_LOG_DEBUG, "%d frame(s)\n", dxac->frames);
    return 0;
}