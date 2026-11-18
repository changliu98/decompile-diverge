int build_open_gop_key_points(AVStream *st)
{
    MOVStreamContext *sc = st->priv_data;
    unsigned i, j, k;
    unsigned sg_index;
    unsigned sample_id = 0;

    if (st->codecpar->codec_id != AV_CODEC_ID_HEVC || !sc->sync_group_count)
        return 0;

    sc->sample_offsets_count = 0;
    for (i = 0; i < sc->ctts_count; i++)
        sc->sample_offsets_count += sc->ctts_data[i].count;

    av_freep(&sc->sample_offsets);
    sc->sample_offsets = av_calloc(sc->sample_offsets_count, sizeof(int32_t));
    if (!sc->sample_offsets)
        return -12;

    k = 0;
    for (i = 0; i < sc->ctts_count; i++)
        for (j = 0; j < sc->ctts_data[i].count; j++)
            sc->sample_offsets[k++] = sc->ctts_data[i].duration;

    sg_index = get_sgpd_sync_index(sc, 21);
    if (!sg_index)
        return 0;

    sc->open_key_samples_count = 0;
    for (i = 0; i < sc->sync_group_count; i++)
        if (sc->sync_group[i].index == sg_index)
            sc->open_key_samples_count += sc->sync_group[i].count;

    av_freep(&sc->open_key_samples);
    sc->open_key_samples = av_calloc(sc->open_key_samples_count, sizeof(int32_t));
    if (!sc->open_key_samples)
        return -12;

    k = 0;
    for (i = 0; i < sc->sync_group_count; i++) {
        if (sc->sync_group[i].index == sg_index)
            for (j = 0; j < sc->sync_group[i].count; j++)
                sc->open_key_samples[k++] = sample_id;
        sample_id += sc->sync_group[i].count;
    }

    sc->min_sample_duration = 0xFFFFFFFF;
    for (i = 0; i < sc->stts_count; i++)
        sc->min_sample_duration = ((sc->min_sample_duration) < (sc->stts_data[i].duration) ? (sc->min_sample_duration) : (sc->stts_data[i].duration));

    return 0;
}