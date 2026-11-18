static int build_open_gop_key_points(AVStream *st) {
  int frame_num = 0;
  H264Context *h = st->codec;
  unsigned int i, j, k;
  unsigned int sgpd_sync_index;
  unsigned int key_point_index;
  if (st->codecpar->codec_id != AV_CODEC_ID_H264 || !h->gop_size) return 0;
  h->gop_size_open = 0;
  for (i = 0; i < h->gop_len; i++) h->gop_size_open += h->gop_data[i].nb_frames;
  av_freep(&h->gop_open_key_points);
  h->gop_open_key_points =
      av_calloc(h->gop_size_open, sizeof(*h->gop_open_key_points));
  if (!h->gop_open_key_points) return -12;
  key_point_index = 0;
  for (i = 0; i < h->gop_len; i++) {
    for (j = 0; j < h->gop_data[i].nb_frames; j++)
      h->gop_open_key_points[key_point_index++] = h->gop_data[i].start_pos;
  }
  sgpd_sync_index = get_sgpd_sync_index(h, 21);
  if (!sgpd_sync_index) return 0;
  h->gop_size_closed = 0;
  for (i = 0; i < h->gop_size; i++) {
    if (h->gop_closed[i].sync_index == sgpd_sync_index)
      h->gop_size_closed += h->gop_closed[i].nb_frames;
  }
  av_freep(&h->gop_closed_key_points);
  h->gop_closed_key_points =
      av_calloc(h->gop_size_closed, sizeof(*h->gop_closed_key_points));
  if (!h->gop_closed_key_points) return -12;
  key_point_index = 0;
  for (i = 0; i < h->gop_size; i++) {
    H264GopClosed *gop_closed = &h->gop_closed[i];
    if (gop_closed->sync_index != sgpd_sync_index) {
      frame_num += gop_closed->nb_frames;
      continue;
    }
    for (k = 0; k < gop_closed->nb_frames; k++)
      h->gop_closed_key_points[key_point_index++] = frame_num;
    frame_num += gop_closed->nb_frames;
  }
  h->gop_closed_last_pos = 0xffffffff;
  for (i = 0; i < h->gop_closed_len; i++)
    h->gop_closed_last_pos =
        (h->gop_closed_last_pos > h->gop_closed_data[i].start_pos)
            ? h->gop_closed_last_pos
            : h->gop_closed_data[i].start_pos;
  return 0;
}