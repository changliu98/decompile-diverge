int build_open_gop_key_points(MOVStreamContext *st) {
    int ret = 0;
    int current_pts = 0;
    int sync_sample_index = 0;
    int keyframe_index = 0;
    
    if (st->field_8->field_0 != 1 || st->field_20 == 0) {
        return 0;
    }

    st->field_48 = 0;
    for (int i = 0; i < st->field_10; i++) {
        st->field_48 += st->field_18[i].field_0;
    }

    av_freep(&st->field_40);
    st->field_40 = av_calloc(st->field_48, 4);
    if (!st->field_40) {
        return -12; // ENOMEM
    }

    keyframe_index = 0;
    for (int i = 0; i < st->field_10; i++) {
        for (int j = 0; j < st->field_18[i].field_0; j++) {
            st->field_40[keyframe_index++] = st->field_18[i].field_4;
        }
    }

    sync_sample_index = get_sgpd_sync_index(st, 0x15);
    if (sync_sample_index == 0) {
        return 0;
    }

    st->field_58 = 0;
    for (int i = 0; i < st->field_20; i++) {
        if (st->field_28[i].field_4 == sync_sample_index) {
            st->field_58 += st->field_28[i].field_0;
        }
    }

    av_freep(&st->field_50);
    st->field_50 = av_calloc(st->field_58, 4);
    if (!st->field_50) {
        return -12; // ENOMEM
    }

    keyframe_index = 0;
    for (int i = 0; i < st->field_20; i++) {
        struct sample_group_entry *entry = &st->field_28[i];
        if (entry->field_4 == sync_sample_index) {
            for (int j = 0; j < entry->field_0; j++) {
                st->field_50[keyframe_index++] = current_pts;
            }
        }
        current_pts += entry->field_0;
    }

    st->field_5c = -1;
    for (int i = 0; i < st->field_0; i++) {
        if (st->field_5c > st->field_8[i].field_4) {
            st->field_5c = st->field_8[i].field_4;
        }
    }

    return 0;
}