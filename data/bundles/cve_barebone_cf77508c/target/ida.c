int __cdecl jpegxl_anim_read_packet(AVFormatContext *s, AVPacket *pkt)
{
  size_t offset; // [rsp+0h] [rbp-40h]
  __int64 size; // [rsp+8h] [rbp-38h]
  int ret; // [rsp+14h] [rbp-2Ch]
  int reta; // [rsp+14h] [rbp-2Ch]
  AVIOContext *pb; // [rsp+18h] [rbp-28h]
  JXLAnimDemuxContext *ctx; // [rsp+20h] [rbp-20h]

  ctx = (JXLAnimDemuxContext *)s->priv_data;
  pb = s->pb;
  offset = 0LL;
  size = avio_size(pb);
  if ( size < 0 )
    return size;
  if ( !size )
    size = 4096LL;
  if ( ctx->initial && size < ctx->initial->size )
    size = ctx->initial->size;
  ret = av_new_packet(pkt, size);
  if ( ret < 0 )
    return ret;
  if ( ctx->initial )
  {
    offset = ctx->initial->size;
    memcpy(pkt->data, ctx->initial->data, offset);
    av_buffer_unref(&ctx->initial);
  }
  reta = avio_read(pb, &pkt->data[offset], size - offset);
  if ( reta < 0 )
    return reta;
  if ( reta < size - offset )
    pkt->size = offset + reta;
  return 0;
}