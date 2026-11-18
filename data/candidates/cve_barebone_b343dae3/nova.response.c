static int build_open_gop_key_points(struct ao *ao)
{
    struct priv *p = ao->priv;
    int i, j, k, l, m, n;

    for (;;) {
        if (p->num_channels == 1 &&!p->stereo3d_enable) {
            n = 0;
            for (i = 0; i < p->num_buffers; i++) {
                for (j = 0; j < p->num_planes; j++) {
                    if (p->buffers[i][j].size > n)
                        n = p->buffers[i][j].size;
                }
            }
            p->buffer_size = n;
        } else {
            p->buffer_size = 0;
            for (i = 0; i < p->num_channels; i++) {
                for (j = 0; j < p->num_planes; j++) {
                    if (p->buffers[i][j].size > p->buffer_size)
                        p->buffer_size = p->buffers[i][j].size;
                }
            }
        }

        p->buffer_size = MPMIN(p->buffer_size, 21);

        if (!p->buffer_size)
            return -1;

        p->buffer_size_bytes = MPMIN(p->buffer_size, 4);

        if (!p->buffer_size_bytes)
            return -1;

        for (i = 0; i < p->num_channels; i++) {
            for (j = 0; j < p->num_planes; j++) {
                if (p->buffers[i][j].size > p->buffer_size_bytes)
                    p->buffer_size_bytes = p->buffers[i][j].size;
            }
        }

        break;
    }

    return 0;
}