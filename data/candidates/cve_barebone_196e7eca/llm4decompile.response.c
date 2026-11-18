int read_tfra(MOVContext *mov, AVIOContext *pb, MOVAtom atom)
{
    MOVFragmentIndex *index = NULL;
    int64_t pos = avio_tell(pb);
    unsigned size = avio_rb32(pb);
    unsigned type = avio_rb32(pb);
    int i, j;

    if (type != (('t') | ('f') | ('r') | ('a')))
        return 1;

    av_log(mov->fc, 40, "found tfra\n");

    index = av_mallocz(sizeof(*index));
    if (!index)
        return -12;

    MOVFragmentIndex **tmp = av_realloc_array(mov->fragment_index_data,
                                              mov->fragment_index_count + 1,
                                              sizeof(*mov->fragment_index_data));
    if (!tmp) {
        av_freep(&index);
        return -12;
    }
    mov->fragment_index_data = tmp;
    mov->fragment_index_data[mov->fragment_index_count++] = index;

    int long_offsets = avio_r8(pb);
    avio_rb24(pb); /* reserved */
    int flags = avio_rb32(pb);
    index->track_id = avio_rb32(pb);
    int reserved = avio_rb32(pb);
    index->item_count = avio_rb32(pb);

    index->items = av_mallocz_array(index->item_count, sizeof(*index->items));
    if (!index->items) {
        index->item_count = 0;
        return -12;
    }

    for (i = 0; i < index->item_count; i++) {
        int64_t time, moof_offset;

        if (long_offsets) {
            time = avio_rb64(pb);
            moof_offset = avio_rb64(pb);
        } else {
            time = avio_rb32(pb);
            moof_offset = avio_rb32(pb);
        }

        index->items[i].time = time;
        index->items[i].moof_offset = moof_offset;

        for (j = 0; j < ((flags >> 4) & 3) + 1; j++)
            avio_r8(pb); /* moof_index */
        for (j = 0; j < ((flags >> 2) & 3) + 1; j++)
            avio_r8(pb); /* trun_index */
        for (j = 0; j < (flags & 3) + 1; j++)
            avio_r8(pb); /* sample_index */
    }

    avio_seek(pb, pos + size, 0);

    return 0;
}