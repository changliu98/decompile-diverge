int apply_window(
    float *buffer,
    int buffer_size,
    int start,
    int end)
{
    int i, j;
    int ret;

    if (buffer[150 + 1]) {
        int win_size = buffer[150 + 1];
        float *win = get_window(buffer, win_size);
        if (!win) {
            ret = 0;
            goto fail;
        }
        for (j = 0; j < buffer[150 + 0]; j++) {
            for (i = 0; i < win_size; i++)
                buffer[150 + 12 + j][i + start] =
                    win[i] * buffer[150 + 12 + j][i + start] +
                    win[win_size - 1 - i] * buffer[150 + 32 + j][i];
        }
    } else {
        int old_win_size = buffer[150 + 1];
        buffer[150 + 1] = buffer_size - end;
        for (j = 0; j < buffer[150 + 0]; j++) {
            for (i = 0; i + end < buffer_size; i++)
                buffer[150 + 32 + j][i] = buffer[150 + 12 + j][i + end];
        }
        if (old_win_size == 0) {
            ret = 0;
            goto fail;
        }
        if (buffer_size < end)
            end = buffer_size;
        buffer[150 + 12 + 1] += end - start;
        ret = end - start;
    }

fail:
    return ret;
}