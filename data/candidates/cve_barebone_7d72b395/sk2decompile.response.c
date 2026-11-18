static int read_new_config_info(MpegAudioContext *s, AVPacket *pkt) {
  int len = pkt->size;
  unsigned char *buf = pkt->data;
  int nb_channels;
  s->new_config_info = 1;
  s->sample_rate = 0;
  s->version = 0;
  s->layer = 0;
  if (s->channel_map) {
    free(s->channel_map);
    s->channel_map = NULL;
  }
  if (!len) return 1;
  s->layer = *buf++;
  s->version = *buf++;
  len -= 2;
  if (!len) return 1;
  s->sample_rate = *buf++ << 16;
  len--;
  if (!len) {
    s->sample_rate += s->sample_rate_index;
    return 1;
  }
  nb_channels = *buf++;
  s->sample_rate += nb_channels;
  len--;
  if (!len) return 1;
  if (len < nb_channels) return 0;
  s->channel_map = malloc(nb_channels);
  if (s->channel_map) {
    int i;
    for (i = 0; i < nb_channels; i++) {
      if (len) {
        s->channel_map[i] = *buf++;
        len--;
      } else
        s->channel_map[i] = i;
    }
  }
  return 1;
}