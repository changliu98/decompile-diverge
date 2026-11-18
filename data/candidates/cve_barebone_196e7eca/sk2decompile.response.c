static int read_tfra(AVFormatContext *s, AVIOContext *pb) {
  TfraChunk *tfra = NULL;
  int64_t pos = avio_tell(pb);
  int64_t size = avio_rb32(pb);
  int version;
  int flags;
  unsigned int i;
  int n_channels;
  int n_blocks;
  int n_samples;
  int j;
  TfraChunk **tfras;
  if (avio_rb32(pb) != 0x72666e71) return 1;
  av_log(s->ctx, 40, "found tfra\n");
  tfra = av_mallocz(sizeof(*tfra));
  if (!tfra) return -12;
  tfras = av_realloc_array(s->priv_data, s->nb_streams + 1, sizeof(*s->priv_data));
  if (!tfras) {
    av_freep(&tfra);
    return -12;
  }
  s->priv_data = tfras;
  s->priv_data[s->nb_streams++] = tfra;
  version = avio_r8(pb);
  avio_rb24(pb);
  tfra->stream_index = avio_rb32(pb);
  flags = avio_rb32(pb);
  tfra->nb_entries = avio_rb32(pb);
  tfra->entries = av_mallocz_array(tfra->nb_entries, sizeof(*tfra->entries));
  if (!tfra->entries) {
    tfra->nb_entries = 0;
    return -12;
  }
  for (i = 0; i < tfra->nb_entries; i++) {
    int64_t start;
    int64_t end;
    if (version == 1) {
      start = avio_rb64(pb);
      end = avio_rb64(pb);
    } else {
      start = avio_rb32(pb);
      end = avio_rb32(pb);
    }
    tfra->entries[i].start = start;
    tfra->entries[i].end = end;
    n_channels = (flags >> 4) & 3;
    n_blocks = (flags >> 2) & 3;
    n_samples = flags & 3;
    for (j = 0; j < n_channels + 1; j++) avio_r8(pb);
    for (j = 0; j < n_blocks + 1; j++) avio_r8(pb);
    for (j = 0; j < n_samples + 1; j++) avio_r8(pb);
  }
  avio_seek(pb, pos + size, 0);
  return 0;
}