int __cdecl build_open_gop_key_points(AVStream *st)
{
  int v1; // ecx
  int v2; // ecx
  uint32_t min_sample_duration; // [rsp+Ch] [rbp-54h]
  uint32_t i_3; // [rsp+10h] [rbp-50h]
  uint32_t j_0; // [rsp+14h] [rbp-4Ch]
  const MOVSbgp *sg; // [rsp+18h] [rbp-48h]
  uint32_t i_2; // [rsp+24h] [rbp-3Ch]
  uint32_t i_1; // [rsp+28h] [rbp-38h]
  unsigned int j; // [rsp+2Ch] [rbp-34h]
  uint32_t i_0; // [rsp+30h] [rbp-30h]
  uint32_t i; // [rsp+34h] [rbp-2Ch]
  MOVStreamContext *sc; // [rsp+38h] [rbp-28h]
  uint32_t cra_index; // [rsp+44h] [rbp-1Ch]
  int sample_id; // [rsp+48h] [rbp-18h]
  int k; // [rsp+4Ch] [rbp-14h]
  int ka; // [rsp+4Ch] [rbp-14h]

  sample_id = 0;
  sc = (MOVStreamContext *)st->priv_data;
  if ( st->codecpar->codec_id != AVCodecID::AV_CODEC_ID_HEVC || !sc->sync_group_count )
    return 0;
  sc->sample_offsets_count = 0;
  for ( i = 0; i < sc->ctts_count; ++i )
    sc->sample_offsets_count += sc->ctts_data[i].count;
  av_freep(&sc->sample_offsets);
  sc->sample_offsets = (int32_t *)av_calloc(sc->sample_offsets_count, 4uLL);
  if ( !sc->sample_offsets )
    return -12;
  k = 0;
  for ( i_0 = 0; i_0 < sc->ctts_count; ++i_0 )
  {
    for ( j = 0; j < sc->ctts_data[i_0].count; ++j )
    {
      v1 = k++;
      sc->sample_offsets[v1] = sc->ctts_data[i_0].duration;
    }
  }
  cra_index = get_sgpd_sync_index(sc, 21);
  if ( !cra_index )
    return 0;
  sc->open_key_samples_count = 0;
  for ( i_1 = 0; i_1 < sc->sync_group_count; ++i_1 )
  {
    if ( sc->sync_group[i_1].index == cra_index )
      sc->open_key_samples_count += sc->sync_group[i_1].count;
  }
  av_freep(&sc->open_key_samples);
  sc->open_key_samples = (int *)av_calloc(sc->open_key_samples_count, 4uLL);
  if ( !sc->open_key_samples )
    return -12;
  ka = 0;
  for ( i_2 = 0; i_2 < sc->sync_group_count; ++i_2 )
  {
    sg = &sc->sync_group[i_2];
    if ( sg->index == cra_index )
    {
      for ( j_0 = 0; j_0 < sg->count; ++j_0 )
      {
        v2 = ka++;
        sc->open_key_samples[v2] = sample_id;
      }
    }
    sample_id += sg->count;
  }
  sc->min_sample_duration = -1;
  for ( i_3 = 0; i_3 < sc->stts_count; ++i_3 )
  {
    if ( sc->min_sample_duration <= sc->stts_data[i_3].duration )
      min_sample_duration = sc->min_sample_duration;
    else
      min_sample_duration = sc->stts_data[i_3].duration;
    sc->min_sample_duration = min_sample_duration;
  }
  return 0;
}