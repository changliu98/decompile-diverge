static int jpegxl_anim_read_packet(AVFormatContext *s, AVPacket *pkt) {
  JpegxlAnimDemuxContext *j = s->priv_data;
  AVIOContext *pb = s->pb;
  size_t header_size = 0;
  int ret;
  int size;
  long size_to_read = avio_size(pb);
  if (size_to_read < 0) return size_to_read;
  if (size_to_read == 0) size_to_read = 4096;
  if (j->header_buffer && j->header_buffer->size < size_to_read)
    size_to_read = j->header_buffer->size;
  ret = av_new_packet(pkt, size_to_read);
  if (ret < 0) return ret;
  if (j->header_buffer) {
    header_size = j->header_buffer->size;
    memcpy(pkt->data, j->header_buffer->data, header_size);
    av_buffer_unref(&j->header_buffer);
  }
  size = avio_read(pb, pkt->data + header_size, size_to_read - header_size);
  if (size < 0) return size;
  if (size < size_to_read - header_size) pkt->size = header_size + size;
  return 0;
}