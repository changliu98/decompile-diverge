__attribute__((used)) static int build_open_gop_key_points(MOVContext *c)
{
    MOVStblContext *stbl = &c->tracks[0]->stbl;
    unsigned int i, j, k, l;
    int err;

    if (stbl->group_count != 1 || !stbl->chunk_group_count) {
        /* Only support single group chunk tables. */
        err = 0;
        goto fail;
    }

    stbl->chunk_group_size = 0;
    for (i = 0; i < stbl->chunk_count; i++)
        stbl->chunk_group_size += stbl->chunk_offset[i].count;

    av_freep(&stbl->chunk_group);
    stbl->chunk_group =
        av_calloc(stbl->chunk_group_size, sizeof(*stbl->chunk_group));
    if (!stbl->chunk_group) {
        err = -12;
        goto fail;
    }

    k = 0;
    i = 0;
    while (1) {
        unsigned int count;
        if (i >= stbl->chunk_count)
            break;
        count = stbl->chunk_offset[i].count;
        for (j = 0; j < count; j++) {
            stbl->chunk_group[k++] = stbl->chunk_offset[i].group;
        }
        i++;
    }

    unsigned int cra_index = get_sgpd_sync_index(c, 21);

    if (!cra_index) {
        err = 0;
        goto fail;
    }

    stbl->sync_group_size = 0;
    for (i = 0; i < stbl->group_count; i++)
        if (stbl->chunk_group_desc[i].group == cra_index)
            stbl->sync_group_size +=
                stbl->chunk_group_desc[i].sample_or_group_count;

    av_freep(&stbl->sync_group);
    stbl->sync_group =
        av_calloc(stbl->sync_group_size, sizeof(*stbl->sync_group));
    if (!stbl->sync_group) {
        err = -12;
        goto fail;
    }

    k = 0;
    i = 0;
    while (1) {
        unsigned int count;
        MOVGroupDescriptionEntry *desc;
        if (i >= stbl->group_count)
            break;
        desc = &stbl->chunk_group_desc[i];
        if (desc->group == cra_index) {
            count = desc->sample_or_group_count;
            for (j = 0; j < count; j++) {
                stbl->sync_group[k++] = c->track_id;
            }
        } else {
            c->track_id += desc->sample_or_group_count;
            i++;
        }
    }

    stbl->min_sample_duration = -1;
    for (i = 0; i < c->track_count; i++) {
        unsigned int duration = c->tracks[i]->track_duration;
        if (duration < stbl->min_sample_duration)
            stbl->min_sample_duration = duration;
    }

    err = 0;
fail:
    return err;
}