__attribute__((used)) static int read_tfra(MOVContext *c, AVIOContext *pb)
{
    MOVFragmentStreamInfo * frag_info = NULL;
    unsigned int i, j;
    int err;
    int version;
    uint32_t flags;
    int fieldlength;
    int64_t time, offset;
    int entry_count;
    int64_t pos = avio_tell(pb);
    unsigned int len = avio_rb32(pb); /* length */
    if (avio_rb32(pb) != MKTAG('t','f','r','a')) {
        err = 1;
        goto fail;
    }
    av_log(c->fc, AV_LOG_DEBUG, "found tfra\n");
    frag_info = av_mallocz(sizeof(*frag_info));
    if (!frag_info) {
        err = -12;
        goto fail;
    }
    { void **nb_ptr = (void **)av_realloc_array(c->fragments, c->nb_fragments + 1, sizeof(*c->fragments)); if (!nb_ptr) { av_freep(&frag_info); err = -12; goto fail; } c->fragments = nb_ptr; };
    c->fragments[c->nb_fragments++] = frag_info;

    version = avio_r8(pb);
    avio_rb24(pb); /* flags */
    frag_info->track_id = avio_rb32(pb);
    fieldlength = avio_rb32(pb);
    entry_count = avio_rb32(pb);
    frag_info->entry_count = entry_count;
    frag_info->entries = av_mallocz_array(entry_count, sizeof(*frag_info->entries));
    if (!frag_info->entries) {
        frag_info->entry_count = 0;
        err = -12;
        goto fail;
    }
    for (i = 0; i < entry_count; i++) {
        if (version == 1) {
            time = avio_rb64(pb);
            offset = avio_rb64(pb);
        } else {
            time = avio_rb32(pb);
            offset = avio_rb32(pb);
        }
        frag_info->entries[i].time = time;
        frag_info->entries[i].pos = offset;
        for (j = 0; j < ((fieldlength >> 4) & 3) + 1; j++)
            avio_r8(pb); /* reserved */
        for (j = 0; j < ((fieldlength >> 2) & 3) + 1; j++)
            avio_r8(pb); /* reserved */
        for (j = 0; j < ((fieldlength >> 0) & 3) + 1; j++)
            avio_r8(pb); /* reserved */
    }
    avio_seek(pb, pos + len, 0);
    err = 0;
fail:
    return err;
}