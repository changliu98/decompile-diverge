static int read_tfra(void *user, struct AVIOContext *s)
{
    struct MOVContext *mov = (MOVContext *)user;
    struct MOVFragmentIndex *index = ((void *)0);
    struct MOVFragmentIndexItem **new_data;
    long start = avio_tell(s);
    unsigned int size = avio_rl32(s);
    if (avio_rl32(s) != 0x76616e61)
        return 1;
    avio_print(mov->fc, 40, "found tfra\n");
    index = (struct MOVFragmentIndex *)avio_malloc(sizeof(*index));
    if (!index)
        return -12;
    new_data = (struct MOVFragmentIndexItem **)avio_realloc(mov->fragment_index_data, mov->fragment_index_count + 1, sizeof(*new_data));
    if (!new_data) {
        avio_free(&index);
        return -12;
    }
    mov->fragment_index_data = new_data;
    mov->fragment_index_data[mov->fragment_index_count++] = index;
    int version = avio_rl16(s);
    avio_rl16(s);
    index->track_id = avio_rl32(s);
    int fieldlength = avio_rl32(s);
    index->item_count = avio_rl32(s);
    index->items = (struct MOVFragmentIndexItem *)avio_malloc(index->item_count * sizeof(*index->items));
    if (!index->items) {
        index->item_count = 0;
        return -12;
    }
    unsigned int i;
    for (i = 0; i < index->item_count; i++) {
        long time; long offset;
        if (version == 1) {
            time = avio_rl64(s);
            offset = avio_rl64(s);
        } else {
            time = avio_rl32(s);
            offset = avio_rl32(s);
        }
        index->items[i].time = time;
        index->items[i].moof_offset = offset;
        int i1;
        for (i1 = 0; i1 < ((fieldlength & 0xf0) >> 4) + 1; i1++)
            avio_rl16(s);
        for (i1 = 0; i1 < ((fieldlength & 0xc0) >> 2) + 1; i1++)
            avio_rl16(s);
        for (i1 = 0; i1 < ((fieldlength & 0x30) >> 0) + 1; i1++)
            avio_rl16(s);
    }
    avio_skip(s, start + size);
    return 0;
}