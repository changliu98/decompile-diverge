int __cdecl dxa_read_header(AVFormatContext *s)
{
  int64_t v1; // rax
  char v3; // [rsp+7h] [rbp-59h]
  unsigned int fsize; // [rsp+8h] [rbp-58h]
  unsigned int size; // [rsp+Ch] [rbp-54h]
  int ret; // [rsp+10h] [rbp-50h]
  char flags; // [rsp+14h] [rbp-4Ch]
  int den; // [rsp+18h] [rbp-48h] BYREF
  int num; // [rsp+1Ch] [rbp-44h] BYREF
  int h; // [rsp+20h] [rbp-40h]
  int w; // [rsp+24h] [rbp-3Ch]
  int32_t fps; // [rsp+28h] [rbp-38h]
  uint32_t tag; // [rsp+2Ch] [rbp-34h]
  AVStream *ast; // [rsp+30h] [rbp-30h]
  AVStream *st; // [rsp+38h] [rbp-28h]
  DXAContext *c; // [rsp+40h] [rbp-20h]
  AVIOContext *pb; // [rsp+48h] [rbp-18h]
  AVFormatContext *sa; // [rsp+50h] [rbp-10h]

  sa = s;
  pb = s->pb;
  c = (DXAContext *)s->priv_data;
  tag = avio_rl32(pb);
  if ( tag != 1096303940 )
    return -1094995529;
  flags = avio_r8(pb);
  c->frames = avio_rb16(pb);
  if ( c->frames )
  {
    fps = avio_rb32(pb);
    if ( fps <= 0 )
    {
      if ( fps >= 0 || fps == 0x80000000 )
      {
        den = 10;
        num = 1;
      }
      else
      {
        den = 100000;
        num = -fps;
      }
    }
    else
    {
      den = 1000;
      num = fps;
    }
    w = avio_rb16(pb);
    h = avio_rb16(pb);
    c->has_sound = 0;
    st = avformat_new_stream(sa, 0LL);
    if ( st )
    {
      if ( avio_rl32(pb) == 1163280727 )
      {
        c->has_sound = 1;
        size = avio_rb32(pb);
        c->vidpos = size + avio_tell(pb);
        x2realloc(pb, 16LL);
        fsize = avio_rl32(pb);
        ast = avformat_new_stream(sa, 0LL);
        if ( !ast )
          return -12;
        ret = ff_get_wav_header(sa, pb, ast->codecpar, fsize, 0);
        if ( ret < 0 )
          return ret;
        if ( ast->codecpar->sample_rate > 0 )
          avpriv_set_pts_info(ast, 64, 1u, ast->codecpar->sample_rate);
        while ( 1 )
        {
          v3 = 0;
          if ( avio_tell(pb) < c->vidpos )
            v3 = ~(avio_feof(pb) != 0);
          if ( (v3 & 1) == 0 )
            break;
          tag = avio_rl32(pb);
          fsize = avio_rl32(pb);
          if ( tag == 1635017060 )
            break;
          x2realloc(pb, fsize);
        }
        c->bpc = (__int64)(c->frames + (unsigned __int64)fsize - 1) / c->frames;
        if ( ast->codecpar->block_align )
        {
          if ( c->bpc > 0x7FFFFFFF - ast->codecpar->block_align + 1 )
            return -1094995529;
          c->bpc = ast->codecpar->block_align * ((ast->codecpar->block_align + c->bpc - 1) / ast->codecpar->block_align);
        }
        c->bytes_left = fsize;
        c->wavpos = avio_tell(pb);
        avio_seek(pb, c->vidpos, 0);
      }
      st->codecpar->codec_type = AVMediaType::AVMEDIA_TYPE_VIDEO;
      st->codecpar->codec_id = AVCodecID::AV_CODEC_ID_DXA;
      st->codecpar->width = w;
      st->codecpar->height = h;
      av_reduce(&den, &num, den, num, 0x7FFFFFFFLL);
      avpriv_set_pts_info(st, 33, num, den);
      if ( (flags & 0xC0) != 0 )
        st->codecpar->height >>= 1;
      c->readvid = c->has_sound == 0;
      v1 = avio_tell(pb);
      c->vidpos = v1;
      sa->start_time = 0LL;
      sa->duration = av_rescale(c->frames, 1000000LL * num, den);
      av_log(sa, 48, "%d frame(s)\n", (unsigned int)c->frames);
      return 0;
    }
    else
    {
      return -12;
    }
  }
  else
  {
    av_log(sa, 16, "File contains no frames ???\n");
    return -1094995529;
  }
}