int __cdecl ImagingPcxDecode(Imaging im, ImagingCodecState state, UINT8 *buf, Py_ssize_t bytes) {
    int stride;
    int bands;
    int i;
    UINT8 *ptr = buf;
    UINT8 count;

    // Mode "1" validation: 1 byte holds 8 pixels, so bytes must be at least xsize / 8
    if (!strcmp(im->mode, "1") && state->xsize > 8 * state->bytes) {
        state->errcode = -1;
        return -1;
    }

    while (1) {
        // Not enough bytes left to read an instruction
        if (bytes < 1) {
            return (int)(ptr - buf);
        }

        // Check for RLE packet (top two bits set)
        if ((*ptr & 0xC0) == 0xC0) {
            // Need at least 2 bytes for the RLE packet
            if (bytes < 2) {
                return (int)(ptr - buf);
            }
            
            count = *ptr & 0x3F; // Lower 6 bits dictate the run length
            while (count--) {
                if (state->x >= state->bytes) {
                    state->errcode = -1;
                    break;
                }
                state->buffer[state->x++] = ptr[1];
            }
            
            ptr += 2;
            bytes -= 2;
        } else {
            // Literal byte packet
            state->buffer[state->x++] = *ptr++;
            bytes--;
        }

        // Check if a full row has been decoded
        if (state->x >= state->bytes) {
            // Deinterleave bands if necessary
            if (state->bytes % state->xsize != 0 && state->bytes > state->xsize) {
                bands = state->bytes / state->xsize;
                stride = state->bytes / bands;
                
                for (i = 1; i < bands; i++) {
                    memmove(&state->buffer[state->xsize * i], 
                            &state->buffer[stride * i], 
                            state->xsize);
                }
            }
            
            // Write decoded row to the image
            state->shuffle(
                (UINT8 *)&im->image[state->y][state->yoff] + (im->pixelsize * state->xoff),
                state->buffer,
                state->xsize
            );
            
            state->x = 0;
            state->y++;
            
            // Check if the whole image is done
            if (state->y >= state->ysize) {
                return -1;
            }
        }
    }
}