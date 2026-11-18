memory error

int __cdecl build_open_gop_key_points(AVStream *st)
{
  MOVStreamContext *sc = (MOVStreamContext *)st->priv_data;
  int sample_id = 0;
  uint32_t cra_index;
  uint32_t i, j, k, ka;
  uint32_t min_sample_duration;

  // Early exit if the codec is not HEVC or there are no sync groups
  if (st->codecpar->codec_id != AV_CODEC_ID_HEVC || !sc->sync_group_count)
    return 0;

  // Calculate total sample offsets based on composition time-to-sample (ctts) data
  sc->sample_offsets_count = 0;
  for (i = 0; i < sc->ctts_count; ++i)
    sc->sample_offsets_count += sc->ctts_data[i].count;

  // Allocate memory for sample offsets
  av_freep(&sc->sample_offsets);
  sc->sample_offsets = (int32_t *)av_calloc(sc->sample_offsets_count, sizeof(int32_t));
  if (!sc->sample_offsets)
    return AVERROR_ENOMEM;

  // Populate sample offsets array
  k = 0;
  for (i = 0; i < sc->ctts_count; ++i)
  {
    for (j = 0; j < sc->ctts_data[i].count; ++j)
    {
      sc->sample_offsets[k++] = sc->ctts_data[i].duration;
    }
  }

  // Get sync sample group entry index for CRA (Clean Random Access, type 21)
  cra_index = get_sgpd_sync_index(sc, 21);
  if (!cra_index)
    return 0;

  // Count total open key samples matching the CRA index
  sc->open_key_samples_count = 0;
  for (i = 0; i < sc->sync_group_count; ++i)
  {
    if (sc->sync_group[i].index == cra_index)
      sc->open_key_samples_count += sc->sync_group[i].count;
  }

  // Allocate memory for open key samples
  av_freep(&sc->open_key_samples);
  sc->open_key_samples = (int *)av_calloc(sc->open_key_samples_count, sizeof(int));
  if (!sc->open_key_samples)
    return AVERROR_ENOMEM;

  // Populate open key samples array with their sample IDs
  ka = 0;
  for (i = 0; i < sc->sync_group_count; ++i)
  {
    const MOVSbgp *sg = &sc->sync_group[i];
    if (sg->index == cra_index)
    {
      for (j = 0; j < sg->count; ++j)
      {
        sc->open_key_samples[ka++] = sample_id;
      }
    }
    sample_id += sg->count;
  }

  // Find the minimum sample duration from the decoding time-to-sample (stts) data
  sc->min_sample_duration = (uint32_t)-1;
  for (i = 0; i < sc->stts_count; ++i)
  {
    if (sc->min_sample_duration > sc->stts_data[i].duration)
      sc->min_sample_duration = sc->stts_data[i].duration;
  }

  return 0;
}