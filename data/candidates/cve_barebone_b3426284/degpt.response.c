int parse_video_info(AVIOContext *pb,AVStream *st)

{
  uint32_t uVar1;
  uint tag_00;
  AVCodecID AVar2;
  int iVar3;
  uint8_t *puVar4;
  uint local_34;
  int ret;
  uint tag;
  uint32_t size_bmp;
  uint16_t size_asf;
  AVStream *st_local;
  AVIOContext *pb_local;
  
  st_local = st;
  pb_local = pb;
  uVar1 = avio_rl32(pb);
  st_local->codecpar->width = uVar1;
  uVar1 = avio_rl32(pb_local);
  st_local->codecpar->height = uVar1;
  avio_skip(pb_local,1);
  size_asf = avio_rl16(pb_local);
  tag_00 = ff_get_bmp_header(pb_local,st_local,&size_bmp);
  st_local->codecpar->codec_tag = tag_00;
  AVar2 = ff_codec_get_id(ff_codec_bmp_tags,tag_00);
  st_local->codecpar->codec_id = AVar2;
  if (size_bmp < size_asf) {
    local_34 = (uint)size_asf;
  }
  else {
    local_34 = size_bmp;
  }
  size_bmp = local_34;
  if (0x28 < local_34) {
    st_local->codecpar->extradata_size = local_34 - 0x28;
    puVar4 = av_malloc((long)(st_local->codecpar->extradata_size + 0x40));
    st_local->codecpar->extradata = puVar4;
    if (puVar4 == (uint8_t *)0x0) {
      st_local->codecpar->extradata_size = 0;
      return -0xc;
    }
    memset(st_local->codecpar->extradata + st_local->codecpar->extradata_size,0,0x40);
    iVar3 = avio_read(pb_local,st_local->codecpar->extradata,st_local->codecpar->extradata_size);
    if (iVar3 < 0) {
      return iVar3;
    }
  }
  return 0;
}