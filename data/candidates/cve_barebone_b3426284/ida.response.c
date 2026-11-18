int __cdecl parse_video_info(AVIOContext *pb, AVStream *st)
{
  AVCodecID id; // eax
  uint8_t *v3; // rax
  uint32_t v5; // [rsp+4h] [rbp-2Ch]
  int ret; // [rsp+8h] [rbp-28h]
  int tag; // [rsp+Ch] [rbp-24h]
  uint32_t size_bmp; // [rsp+10h] [rbp-20h] BYREF
  uint16_t size_asf; // [rsp+16h] [rbp-1Ah]
  AVStream *sta; // [rsp+18h] [rbp-18h]
  AVIOContext *pba; // [rsp+20h] [rbp-10h]

  pba = pb;
  sta = st;
  st->codecpar->width = avio_rl32(pb);
  sta->codecpar->height = avio_rl32(pba);
  avio_skip(pba, 1LL);
  size_asf = avio_rl16(pba);
  tag = ff_get_bmp_header(pba, sta, &size_bmp);
  sta->codecpar->codec_tag = tag;
  id = ff_codec_get_id(&ff_codec_bmp_tags, tag);
  sta->codecpar->codec_id = id;
  if ( size_asf <= size_bmp )
    v5 = size_bmp;
  else
    v5 = size_asf;
  size_bmp = v5;
  if ( v5 <= 0x28 )
    return 0;
  sta->codecpar->extradata_size = size_bmp - 40;
  v3 = (uint8_t *)av_malloc(sta->codecpar->extradata_size + 64);
  sta->codecpar->extradata = v3;
  if ( v3 )
  {
    memset(&sta->codecpar->extradata[sta->codecpar->extradata_size], 0, 0x40uLL);
    ret = avio_read(pba, sta->codecpar->extradata, sta->codecpar->extradata_size);
    if ( ret < 0 )
      return ret;
    return 0;
  }
  sta->codecpar->extradata_size = 0;
  return -12;
}