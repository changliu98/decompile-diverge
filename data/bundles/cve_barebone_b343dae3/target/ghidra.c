int build_open_gop_key_points(AVStream *st)

{
  MOVStreamContext *sc_00;
  uint32_t uVar1;
  int32_t *piVar2;
  int *piVar3;
  MOVSbgp *pMVar4;
  uint local_5c;
  uint32_t i_4;
  uint32_t j_1;
  MOVSbgp *sg;
  uint32_t i_3;
  uint32_t i_2;
  int j;
  uint32_t i_1;
  uint32_t i;
  MOVStreamContext *sc;
  uint32_t cra_index;
  int sample_id;
  int k;
  AVStream *st_local;
  int local_c;
  
  sample_id = 0;
  sc_00 = st->priv_data;
  if ((st->codecpar->codec_id == AV_CODEC_ID_HEVC) && (sc_00->sync_group_count != 0)) {
    sc_00->sample_offsets_count = 0;
    for (i = 0; i < sc_00->ctts_count; i = i + 1) {
      sc_00->sample_offsets_count = sc_00->ctts_data[i].count + sc_00->sample_offsets_count;
    }
    av_freep(&sc_00->sample_offsets);
    piVar2 = av_calloc((long)sc_00->sample_offsets_count,4);
    sc_00->sample_offsets = piVar2;
    if (sc_00->sample_offsets == (int32_t *)0x0) {
      local_c = -0xc;
    }
    else {
      k = 0;
      for (i_1 = 0; i_1 < sc_00->ctts_count; i_1 = i_1 + 1) {
        for (j = 0; (uint)j < sc_00->ctts_data[i_1].count; j = j + 1) {
          sc_00->sample_offsets[k] = sc_00->ctts_data[i_1].duration;
          k = k + 1;
        }
      }
      uVar1 = get_sgpd_sync_index(sc_00,0x15);
      if (uVar1 == 0) {
        local_c = 0;
      }
      else {
        sc_00->open_key_samples_count = 0;
        for (i_2 = 0; i_2 < sc_00->sync_group_count; i_2 = i_2 + 1) {
          if (sc_00->sync_group[i_2].index == uVar1) {
            sc_00->open_key_samples_count =
                 sc_00->sync_group[i_2].count + sc_00->open_key_samples_count;
          }
        }
        av_freep(&sc_00->open_key_samples);
        piVar3 = av_calloc((long)sc_00->open_key_samples_count,4);
        sc_00->open_key_samples = piVar3;
        if (sc_00->open_key_samples == (int *)0x0) {
          local_c = -0xc;
        }
        else {
          k = 0;
          for (i_3 = 0; i_3 < sc_00->sync_group_count; i_3 = i_3 + 1) {
            pMVar4 = sc_00->sync_group + i_3;
            if (pMVar4->index == uVar1) {
              for (j_1 = 0; j_1 < pMVar4->count; j_1 = j_1 + 1) {
                sc_00->open_key_samples[k] = sample_id;
                k = k + 1;
              }
            }
            sample_id = pMVar4->count + sample_id;
          }
          sc_00->min_sample_duration = 0xffffffff;
          for (i_4 = 0; i_4 < sc_00->stts_count; i_4 = i_4 + 1) {
            if (sc_00->stts_data[i_4].duration < sc_00->min_sample_duration) {
              local_5c = sc_00->stts_data[i_4].duration;
            }
            else {
              local_5c = sc_00->min_sample_duration;
            }
            sc_00->min_sample_duration = local_5c;
          }
          local_c = 0;
        }
      }
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}