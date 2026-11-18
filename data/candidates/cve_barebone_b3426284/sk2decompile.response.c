static int parse_video_info(AVIOContext *pb, AVStream *st) {
  unsigned int bmp_header_size, bmp_header_size_read;
  int ret;
  st->codecpar->width = avio_rl32(pb);
  st->codecpar->height = avio_rl32(pb);
  avio_skip(pb, 1);
  bmp_header_size = avio_rl16(pb);
  ret = ff_get_bmp_header(pb, st, &bmp_header_size_read);
  st->codecpar->extradata_size = ret;
  st->codecpar->codec_id = ff_codec_get_id(&ff_bmp_codec_ids, ret);
  bmp_header_size_read =
      bmp_header_size > bmp_header_size_read ? bmp_header_size : bmp_header_size_read;
  if (bmp_header_size_read < 40) return 0;
  st->codecpar->extradata_size = bmp_header_size_read - 40;
  st->codecpar->extradata = av_malloc(st->codecpar->extradata_size + 64);
  if (!st->codecpar->extradata) {
    st->codecpar->extradata_size = 0;
    return -12;
  }
  memset(st->codecpar->extradata + st->codecpar->extradata_size, 0, 64);
  ret = avio_read(pb, st->codecpar->extradata, st->codecpar->extradata_size);
  if (ret < 0) return ret;
  return 0;
}