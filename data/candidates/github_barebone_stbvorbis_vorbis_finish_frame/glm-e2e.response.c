int vorbis_finish_frame(stb_vorbis *f, int len, int left, int right) {
    int prev = f->previous_window;
    int n = f->blocksize[prev];
    float *window = f->windows[prev];
    int i, j;

    if (f->previous_window) {
        if (!window) {
            return 0;
        }
        for (i = 0; i < f->channels; i++) {
            for (j = 0; j < n; j++) {
                float a = f->channel_buffers[i][left + j];
                float b = f->previous_window[j];
                float c = f->previous_window[n - 1 - j];
                f->channel_buffers[i][left + j] = a * b + c * window[n - 1 - j];
            }
        }
    }

    f->previous_window = f->blocksize[f->blocksize[0] == f->blocksize[1]];
    f->previous_length = len - right;

    // Copy the right half of the current block to previous_window
    for (i = 0; i < f->channels; i++) {
        for (j = 0; j < right; j++) {
            f->previous_window[j] = f->channel_buffers[i][left + j];
        }
    }

    if (!prev) {
        return 0;
    }

    if (len < right) {
        right = len;
    }

    f->current_loc += right - left;
    return right - left;
}