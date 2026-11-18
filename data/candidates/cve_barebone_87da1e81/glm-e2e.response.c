int dxa_read_header(AVFormatContext_Decl *s) {
    DXAContext *c = (DXAContext *)s->pb; // Note: In actual FFmpeg, it's s->priv_data
    AVIOContext *pb = (AVIOContext *)s->pb;
    
    int tag = avio_rl32(pb);
    if (tag != 0x41584544) // "DEXA"
        return AVERROR_INVALIDDATA;
    
    int type = avio_r8(pb);
    c->frames = avio_rb16(pb);
    if (!c->frames) {
        av_log(s, 0x10, "0 frames\n");
        return AVERROR_INVALIDDATA;
    }
    
    int fps = avio_rb32(pb);
    int rate, scale;
    if (fps > 0) {
        scale = 1000;
        rate = fps;
    } else if (fps < 0 && fps > -0x80000000) { // Check for INT32_MIN overflow
        scale = 100000;
        rate = -fps;
    } else {
        scale = 10;
        rate = 1;
    }
    
    int width = avio_rb16(pb);
    int height = avio_rb16(pb);
    c->has_audio = 0;
    
    AVStream *st = avformat_new_stream(s, 0);
    if (!st)
        return AVERROR_ENOMEM;
        
    if (avio_rl32(pb) == 0x45564157) { // "WAVE"
        c->has_audio = 1;
        int size = avio_rb32(pb);
        c->data_start = avio_tell(pb) + size;
        avio_skip(pb, 16);
        int ast_size = avio_rl32(pb);
        
        AVStream *ast = avformat_new_stream(s, 0);
        if (!ast)
            return AVERROR_ENOMEM;
            
        int ret = ff_get_wav_header(s, pb, ast->codecpar, ast_size, 0);
        if (ret < 0)
            return ret;
            
        if (ast->codecpar->sample_rate > 0)
            avpriv_set_pts_info(ast, 64, 1, ast->codecpar->sample_rate);
            
        while (avio_tell(pb) < c->data_start && !avio_feof(pb)) {
            tag = avio_rl32(pb);
            size = avio_rl32(pb);
            if (tag == 0x61746164) // "data"
                break;
            avio_skip(pb, size);
        }
        
        c->frame_rate = (size + c->frames - 1) / c->frames;
        if (ast->codecpar->block_align) {
            if (c->frame_rate > 0x7fffffff - ast->codecpar->block_align + 1)
                return AVERROR_INVALIDDATA;
            c->frame_rate = ((c->frame_rate + ast->codecpar->block_align - 1) / ast->codecpar->block_align) * ast->codecpar->block_align;
        }
        c->bytes_left = size;
        c->audio_start = avio_tell(pb);
        avio_seek(pb, c->data_start, 0);
    }
    
    st->codecpar->codec_type = 0; // AVMEDIA_TYPE_VIDEO
    st->codecpar->bit_rate = 0x15000;
    st->codecpar->width = width;
    st->codecpar->height = height;
    
    av_reduce(&scale, &rate, scale, rate, 0x7fffffff);
    avpriv_set_pts_info(st, 33, rate, scale);
    
    if (type & 0xC0) {
        st->codecpar->height >>= 1;
    }
    
    c->no_text = !c->has_audio;
    c->data_start = avio_tell(pb);
    s->bit_rate = 0;
    s->duration = av_rescale(c->frames, (int64_t)rate * 1000000, scale);
    
    av_log(s, 0x30, "%d frames\n", c->frames);
    
    return 0;
}