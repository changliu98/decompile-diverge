static int mov_init_sample_offsets(struct AVStream *stream)
{
    struct MOVStreamContext *mov = stream->priv_data;
    unsigned int i;
    int sample_id = 0;
    if (stream->codecpar->codec_id != AV_CODEC_ID_HEVC || mov->sync_group_count == 0)
        return 0;
    mov->sample_offsets_count = 0;
    for (i = 0; i < mov->ctts_count; i++)
        mov->sample_offsets_count += mov->ctts_data[i].count;
    av_freep(&mov->sample_offsets);
    mov->sample_offsets = av_mallocz(mov->sample_offsets_count * sizeof(int));
    if (!mov->sample_offsets)
        return -12;
    for (i = 0, sample_id = 0; i < mov->ctts_count; i++)
        for (unsigned int j = 0; j < mov->ctts_data[i].count; j++)
            mov->sample_offsets[sample_id++] = mov->ctts_data[i].duration;
    unsigned int cra_index = mov_get_cra_index(mov, 21);
    if (cra_index == 0)
        return 0;
    mov->open_key_samples_count = 0;
    for (i = 0; i < mov->sync_group_count; i++)
        if (mov->sync_group[i].index == cra_index)
            mov->open_key_samples_count += mov->sync_group[i].count;
    av_freep(&mov->open_key_samples);
    mov->open_key_samples = av_mallocz(mov->open_key_samples_count * sizeof(int));
    if (!mov->open_key_samples)
        return -12;
    for (i = 0, sample_id = 0; i < mov->sync_group_count; i++) {
        struct MOVSbgp *sg = &mov->sync_group[i];
        if (sg->index == cra_index)
            for (unsigned int j = 0; j < sg->count; j++)
                mov->open_key_samples[sample_id++] = (int)i;
        sample_id += sg->count;
    }
    unsigned int min_sample_duration = 0xFFFFFFFF;
    for (i = 0; i < mov->stts_count; i++)
        if (mov->stts_data[i].duration < min_sample_duration)
            min_sample_duration = mov->stts_data[i].duration;
        else
            min_sample_duration = mov->stts_data[i].duration;
    mov->min_sample_duration = min_sample_duration;
    return 0;
}