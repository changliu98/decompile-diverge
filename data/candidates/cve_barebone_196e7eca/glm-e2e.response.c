int read_tfra(MOVContext *mov, AVIOContext *pb) {
    TfraTrack *tfra = NULL;
    int64_t start_pos;
    uint32_t size;
    uint32_t version_flags;
    uint32_t length_size_flags;
    int i, j;

    start_pos = avio_tell(pb);
    size = avio_rb32(pb);
    
    if (avio_rb32(pb) != MKTAG('t', 'f', 'r', 'a')) {
        return 1;
    }
    
    av_log(mov->av_class, 0x28, "tfra\n");
    
    tfra = av_mallocz(sizeof(TfraTrack));
    if (!tfra) {
        return AVERROR_INVALIDDATA;
    }
    
    TfraTrack **tracks = av_realloc_array(mov->tracks, mov->track_count + 1, sizeof(TfraTrack *));
    if (!tracks) {
        av_freep(&tfra);
        return AVERROR_INVALIDDATA;
    }
    mov->tracks = tracks;
    mov->tracks[mov->track_count++] = tfra;
    
    version_flags = avio_r8(pb);
    avio_rb24(pb);
    tfra->track_id = avio_rb32(pb);
    length_size_flags = avio_rb32(pb);
    tfra->entry_count = avio_rb32(pb);
    
    tfra->entries = av_mallocz_array(tfra->entry_count, sizeof(TfraEntry));
    if (!tfra->entries) {
        tfra->entry_count = 0;
        return AVERROR_INVALIDDATA;
    }
    
    for (i = 0; i < tfra->entry_count; i++) {
        if (version_flags == 1) {
            tfra->entries[i].time = avio_rb64(pb);
            tfra->entries[i].offset = avio_rb64(pb);
        } else {
            tfra->entries[i].time = avio_rb32(pb);
            tfra->entries[i].offset = avio_rb32(pb);
        }
        
        // Skip auxiliary information fields based on length_size_flags
        for (j = 0; j < ((length_size_flags >> 4) & 3) + 1; j++) {
            avio_r8(pb);
        }
        for (j = 0; j < ((length_size_flags >> 2) & 3) + 1; j++) {
            avio_r8(pb);
        }
        for (j = 0; j < (length_size_flags & 3) + 1; j++) {
            avio_r8(pb);
        }
    }
    
    avio_seek(pb, start_pos + size, 0);
    return 0;
}