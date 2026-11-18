__attribute__((noinline))
static int dxa_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    DXAContext *c = s->priv_data;
    AVStream *st, *ast;
    uint32_t tag;
    int32_t fps;
    int w, h;
    int num, den;
    int flags;
    int ret;

    tag = avio_rl32(pb);
    if (tag != MKTAG('D', 'E', 'X', 'A'))
        return AVERROR_INVALIDDATA;
    flags = avio_r8(pb);
    c->frames = avio_rb16(pb);
    if(!c->frames){
        av_log(s, AV_LOG_ERROR, "File contains no frames ???\n");
        return AVERROR_INVALIDDATA;
    }

    fps = avio_rb32(pb);
    if(fps > 0){
        den = 1000;
        num = fps;
    }else if (fps < 0 && fps > INT_MIN){
        den = 100000;
        num = -fps;
    }else{
        den = 10;
        num = 1;
    }
    w = avio_rb16(pb);
    h = avio_rb16(pb);
    c->has_sound = 0;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    // Parse WAV data header
    if(avio_rl32(pb) == MKTAG('W', 'A', 'V', 'E')){
        uint32_t size, fsize;
        c->has_sound = 1;
        size = avio_rb32(pb);
        c->vidpos = avio_tell(pb) + size;
        avio_skip(pb, 16);
        fsize = avio_rl32(pb);

        ast = avformat_new_stream(s, NULL);
        if (!ast)
            return AVERROR(ENOMEM);
        ret = ff_get_wav_header(s, pb, ast->codecpar, fsize, 0);
        if (ret < 0)
            return ret;
        if (ast->codecpar->sample_rate > 0)
            avpriv_set_pts_info(ast, 64, 1, ast->codecpar->sample_rate);
        // find 'data' chunk
        while(avio_tell(pb) < c->vidpos && !avio_feof(pb)){
            tag = avio_rl32(pb);
            fsize = avio_rl32(pb);
            if(tag == MKTAG('d', 'a', 't', 'a')) break;
            avio_skip(pb, fsize);
        }
        c->bpc = (fsize + (int64_t)c->frames - 1) / c->frames;
        if(ast->codecpar->block_align) {
            if (c->bpc > INT_MAX - ast->codecpar->block_align + 1)
                return AVERROR_INVALIDDATA;
            c->bpc = ((c->bpc + ast->codecpar->block_align - 1) / ast->codecpar->block_align) * ast->codecpar->block_align;
        }
        c->bytes_left = fsize;
        c->wavpos = avio_tell(pb);
        avio_seek(pb, c->vidpos, SEEK_SET);
    }

    /* now we are ready: build format streams */
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_DXA;
    st->codecpar->width      = w;
    st->codecpar->height     = h;
    av_reduce(&den, &num, den, num, (1UL<<31)-1);
    avpriv_set_pts_info(st, 33, num, den);
    /* flags & 0x80 means that image is interlaced,
     * flags & 0x40 means that image has double height
     * either way set true height
     */
    if(flags & 0xC0){
        st->codecpar->height >>= 1;
    }
    c->readvid = !c->has_sound;
    c->vidpos  = avio_tell(pb);
    s->start_time = 0;
    s->duration = av_rescale(c->frames, AV_TIME_BASE * (int64_t)num, den);
    av_log(s, AV_LOG_DEBUG, "%d frame(s)\n",c->frames);

    return 0;
}