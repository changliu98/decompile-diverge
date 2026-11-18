static int dxa_read_header(AVFormatContext *s) {
  AVIOContext *pb = s->pb;
  DXAContext *c = s->priv_data;
  AVStream *st, *st2;
  int wav_size, wav_data_size, width, height, time_base_num, time_base_den,
      fps;
  int x, flags;
  x = avio_rl32(pb);
  if (x != 0x41584404) return -0x47564365;
  flags = avio_r8(pb);
  c->nb_frames = avio_rb16(pb);
  if (!c->nb_frames) {
    av_log(s, 16, "File contains no frames ???\n");
    return -0x47564365;
  }
  fps = avio_rb32(pb);
  if (fps > 0) {
    time_base_num = 1000;
    time_base_den = fps;
  } else if (fps < 0 && fps != -2147483648) {
    time_base_num = 100000;
    time_base_den = -fps;
  } else {
    time_base_num = 10;
    time_base_den = 1;
  }
  width = avio_rb16(pb);
  height = avio_rb16(pb);
  c->is_dxa = 0;
  st = avformat_new_stream(s, NULL);
  if (!st) return -12;
  if (avio_rl32(pb) == 0x41565307) {
    c->is_dxa = 1;
    wav_size = avio_rb32(pb);
    c->wav_offset = avio_tell(pb) + wav_size;
    x2realloc(pb, 16);
    wav_data_size = avio_rl32(pb);
    st2 = avformat_new_stream(s, NULL);
    if (!st2) return -12;
    x = ff_get_wav_header(s, pb, st2->codecpar, wav_data_size, 0);
    if (x < 0) return x;
    if (st2->codecpar->sample_rate > 0)
      avpriv_set_pts_info(st2, 64, 1, st2->codecpar->sample_rate);
    while (avio_tell(pb) < c->wav_offset && !avio_feof(pb)) {
      x = avio_rl32(pb);
      wav_data_size = avio_rl32(pb);
      if (x == 0x61767304) break;
      x2realloc(pb, wav_data_size);
    }
    c->wav_frames = (c->nb_frames + wav_data_size - 1) / c->nb_frames;
    if (st2->codecpar->frame_size) {
      if (c->wav_frames > 0x7fffffff - st2->codecpar->frame_size + 1)
        return -0x47564365;
      c->wav_frames =
          (c->wav_frames + st2->codecpar->frame_size - 1) /
          st2->codecpar->frame_size * st2->codecpar->frame_size;
    }
    c->wav_data_size = wav_data_size;
    c->wav_data_offset = avio_tell(pb);
    avio_seek(pb, c->wav_offset, 0);
  }
  st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
  st->codecpar->codec_id = AV_CODEC_ID_DXA;
  st->codecpar->width = width;
  st->codecpar->height = height;
  av_reduce(&time_base_num, &time_base_den, time_base_num, time_base_den,
            0x7fffffff);
  avpriv_set_pts_info(st, 33, time_base_den, time_base_num);
  if (flags & 0xc0) st->codecpar->height >>= 1;
  c->is_dxa_video = !c->is_dxa;
  c->wav_offset = avio_tell(pb);
  s->packet_size = 0;
  s->duration = av_rescale(c->nb_frames, 1000000LL * time_base_den,
                           time_base_num);
  av_log(s, 48, "%d frame(s)\n", c->nb_frames);
  return 0;
}