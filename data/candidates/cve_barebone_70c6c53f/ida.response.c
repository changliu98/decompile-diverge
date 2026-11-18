int __cdecl parse_speex_extradata(AVCodecContext *avctx, const uint8_t *extradata, int extradata_size)
{
  unsigned int le32; // eax
  unsigned int v4; // eax
  unsigned int v5; // eax
  unsigned int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  unsigned int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  const uint8_t *buf; // [rsp+10h] [rbp-30h] BYREF
  SpeexContext *s; // [rsp+18h] [rbp-28h]
  int extradata_sizea; // [rsp+24h] [rbp-1Ch]
  const uint8_t *extradataa; // [rsp+28h] [rbp-18h]
  AVCodecContext *avctxa; // [rsp+30h] [rbp-10h]

  avctxa = avctx;
  extradataa = extradata;
  extradata_sizea = extradata_size;
  s = (SpeexContext *)avctx->priv_data;
  buf = (const uint8_t *)av_strnstr((const char *)extradata, "Speex   ", extradata_size);
  if ( !buf )
    return -1094995529;
  buf += 28;
  le32 = bytestream_get_le32(&buf);
  s->version_id = le32;
  buf += 4;
  v4 = bytestream_get_le32(&buf);
  s->rate = v4;
  if ( s->rate <= 0 )
    return -1094995529;
  v5 = bytestream_get_le32(&buf);
  s->mode = v5;
  if ( s->mode >= 3u )
    return -1094995529;
  v6 = bytestream_get_le32(&buf);
  s->bitstream_version = v6;
  if ( s->bitstream_version != 4 )
    return -1094995529;
  v7 = bytestream_get_le32(&buf);
  s->nb_channels = v7;
  if ( s->nb_channels <= 0 || s->nb_channels > 2 )
    return -1094995529;
  v8 = bytestream_get_le32(&buf);
  s->bitrate = v8;
  v9 = bytestream_get_le32(&buf);
  s->frame_size = v9;
  if ( s->frame_size < 160 << (s->mode > 0) )
    return -1094995529;
  s->frame_size *= (s->mode > 0) + 1;
  v10 = bytestream_get_le32(&buf);
  s->vbr = v10;
  v11 = bytestream_get_le32(&buf);
  s->frames_per_packet = v11;
  if ( s->frames_per_packet <= 0
    || s->frames_per_packet > 64
    || s->frames_per_packet >= 0x7FFFFFFF / s->nb_channels / s->frame_size )
  {
    return -1094995529;
  }
  v12 = bytestream_get_le32(&buf);
  s->extra_headers = v12;
  return 0;
}