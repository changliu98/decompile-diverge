int parse_speex_extradata(AVCodecContext *avctx,uint8_t *extradata,int extradata_size)

{
  ulong uVar1;
  uint uVar2;
  char *pcVar3;
  uint8_t *buf;
  SpeexContext *s;
  int extradata_size_local;
  uint8_t *extradata_local;
  AVCodecContext *avctx_local;
  int local_c;
  
  s = avctx->priv_data;
  extradata_size_local = extradata_size;
  extradata_local = extradata;
  avctx_local = avctx;
  pcVar3 = av_strnstr((char *)extradata,"Speex   ",(long)extradata_size);
  if (pcVar3 == (char *)0x0) {
    local_c = -0x41444e49;
  }
  else {
    buf = (uint8_t *)(pcVar3 + 0x1c);
    uVar2 = bytestream_get_le32(&buf);
    s->version_id = uVar2;
    buf = buf + 4;
    uVar2 = bytestream_get_le32(&buf);
    s->rate = uVar2;
    if (s->rate < 1) {
      local_c = -0x41444e49;
    }
    else {
      uVar2 = bytestream_get_le32(&buf);
      s->mode = uVar2;
      if ((s->mode < 0) || (2 < s->mode)) {
        local_c = -0x41444e49;
      }
      else {
        uVar2 = bytestream_get_le32(&buf);
        s->bitstream_version = uVar2;
        if (s->bitstream_version == 4) {
          uVar2 = bytestream_get_le32(&buf);
          s->nb_channels = uVar2;
          if ((s->nb_channels < 1) || (2 < s->nb_channels)) {
            local_c = -0x41444e49;
          }
          else {
            uVar2 = bytestream_get_le32(&buf);
            s->bitrate = uVar2;
            uVar2 = bytestream_get_le32(&buf);
            s->frame_size = uVar2;
            if (s->frame_size < 0xa0 << (0 < s->mode)) {
              local_c = -0x41444e49;
            }
            else {
              s->frame_size = ((0 < s->mode) + 1) * s->frame_size;
              uVar2 = bytestream_get_le32(&buf);
              s->vbr = uVar2;
              uVar2 = bytestream_get_le32(&buf);
              s->frames_per_packet = uVar2;
              if (((s->frames_per_packet < 1) || (0x40 < s->frames_per_packet)) ||
                 (uVar1 = 0x7fffffff / (long)s->nb_channels,
                 (int)((long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) /
                      (long)s->frame_size) <= s->frames_per_packet)) {
                local_c = -0x41444e49;
              }
              else {
                uVar2 = bytestream_get_le32(&buf);
                s->extra_headers = uVar2;
                local_c = 0;
              }
            }
          }
        }
        else {
          local_c = -0x41444e49;
        }
      }
    }
  }
  return local_c;
}