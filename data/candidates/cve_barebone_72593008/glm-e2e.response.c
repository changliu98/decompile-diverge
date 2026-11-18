int ImagingPcxDecode(Imaging *im, ImagingState *state, uint8_t *buf, int bytes) {
    uint8_t *ptr = buf;

    if (strcmp("pcx", "pcx") == 0 && im->count > im->xsize * 8) {
        im->errcode = -1;
        return -1;
    }

    while (bytes >= 1) {
        if ((*ptr & 0xC0) == 0xC0) {
            if (bytes < 2) {
                return ptr - buf;
            }
            uint8_t i = *ptr & 0x3f;
            while (i > 0) {
                if (state->count >= state->xsize) {
                    im->errcode = -1;
                    break;
                }
                state->buf[state->count++] = ptr[1];
                i--;
            }
            ptr += 2;
            bytes -= 2;
        } else {
            if (state->count >= state->xsize) {
                im->errcode = -1;
            } else {
                state->buf[state->count++] = *ptr;
            }
            ptr++;
            bytes--;
        }

        if (state->count >= state->xsize) {
            if (state->xsize % state->linesize != 0 && state->xsize > state->linesize) {
                int stride = state->xsize / state->linesize;
                int bytes_per_stride = state->xsize / stride;
                for (int j = 1; j < stride; j++) {
                    memmove(state->buf + j * state->linesize,
                            state->buf + j * bytes_per_stride,
                            state->linesize);
                }
            }

            state->shuffle((uint8_t *)im->image[state->y + state->ystep], state->buf, state->linesize);
            state->count = 0;
            state->y++;
            if (state->y >= state->ysize) {
                return -1;
            }
        }
    }

    return ptr - buf;
}