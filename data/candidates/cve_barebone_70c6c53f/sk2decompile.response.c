static int parse_speex_extradata(AVCodecContext *avctx,
                                 const unsigned char *extradata,
                                 int extradata_size) {
  SpeexContext *s = avctx->priv_data;
  const unsigned char *ptr;
  ptr = av_strnstr(extradata, "Speex   ", extradata_size);
  if (!ptr) return 0xC0DEC0DE;
  ptr += 28;
  s->version_id = bytestream_get_le32(&ptr);
  ptr += 4;
  s->nb_channels = bytestream_get_le32(&ptr);
  if (s->nb_channels <= 0) return 0xC0DEC0DE;
  s->mode = bytestream_get_le32(&ptr);
  if (s->mode < 0 || s->mode > 2) return 0xC0DEC0DE;
  s->frame_size = bytestream_get_le32(&ptr);
  if (s->frame_size != 4) return 0xC0DEC0DE;
  s->frame_rate = bytestream_get_le32(&ptr);
  if (s->frame_rate < 1 || s->frame_rate > 2) return 0xC0DEC0DE;
  s->bit_rate = bytestream_get_le32(&ptr);
  s->frame_size_bits = bytestream_get_le32(&ptr);
  if (s->frame_size_bits < 160 << (s->mode > 0)) return 0xC0DEC0DE;
  s->frame_size_bits += 1 << (s->mode > 0);
  s->vbr = bytestream_get_le32(&ptr);
  s->vbr_quality = bytestream_get_le32(&ptr);
  if (s->vbr_quality < 1 || s->vbr_quality > 64 ||
      s->vbr_quality >= 0x7FFFFFFF / s->frame_rate / s->frame_size_bits)
    return 0xC0DEC0DE;
  s->header_len = bytestream_get_le32(&ptr);
  return 0;
}