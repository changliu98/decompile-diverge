int AVI_read_audio(avi_t *avi, void *buf, int size, int *continuous) {
    int bytes_read = 0;
    int remaining = size;
    int track = avi->audio_track;

    if (avi->field_8 == 0) {
        AVI_errno = 7;
        return -1;
    }

    if (avi->tracks[track].index == NULL) {
        AVI_errno = 13;
        return -1;
    }

    if (size == 0) {
        avi->tracks[track].cur_frame++;
        avi->tracks[track].cur_offset = 0;
    }

    *continuous = 1;

    while (remaining > 0) {
        int chunk_left = avi->tracks[track].index[avi->tracks[track].cur_frame].size - avi->tracks[track].cur_offset;

        if (chunk_left == 0) {
            if (avi->tracks[track].cur_frame >= avi->tracks[track].total_frames - 1) {
                return bytes_read;
            }
            avi->tracks[track].cur_frame++;
            avi->tracks[track].cur_offset = 0;
            *continuous = 0;
            continue;
        }

        int to_read = remaining < chunk_left ? remaining : chunk_left;
        uint64_t pos = avi->tracks[track].index[avi->tracks[track].cur_frame].pos + avi->tracks[track].cur_offset;
        
        gf_fseek(avi->file, pos, 0);
        int read = avi_read(avi->file, (char *)buf + bytes_read, to_read);
        
        if (read != to_read) {
            AVI_errno = 3;
            return -1;
        }

        remaining -= to_read;
        bytes_read += to_read;
        avi->tracks[track].cur_offset += to_read;
    }

    return bytes_read;
}