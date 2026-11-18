int jpegxl_anim_read_packet(AVFormatContext *s,AVPacket *pkt)

{
  AVBufferRef **buf;
  AVIOContext *s_00;
  size_t offset;
  int64_t size;
  int ret;
  AVIOContext *pb;
  JXLAnimDemuxContext *ctx;
  AVPacket *pkt_local;
  AVFormatContext *s_local;
  int local_c;
  
  buf = s->priv_data;
  s_00 = s->pb;
  offset = 0;
  size = avio_size(s_00);
  if (size < 0) {
    local_c = (int)size;
  }
  else {
    if (size == 0) {
      size = 0x1000;
    }
    if ((*buf != (AVBufferRef *)0x0) && ((ulong)size < (*buf)->size)) {
      size = (*buf)->size;
    }
    local_c = av_new_packet(pkt,(int)size);
    if (-1 < local_c) {
      if (*buf != (AVBufferRef *)0x0) {
        offset = (*buf)->size;
        memcpy(pkt->data,(*buf)->data,offset);
        av_buffer_unref(buf);
      }
      local_c = avio_read(s_00,pkt->data + offset,(int)size - (int)offset);
      if (-1 < local_c) {
        if ((ulong)(long)local_c < size - offset) {
          pkt->size = local_c + (int)offset;
        }
        local_c = 0;
      }
    }
  }
  return local_c;
}