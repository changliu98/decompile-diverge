nsgif_error __cdecl nsgif_frame_decode(nsgif_t *gif, uint32_t frame, nsgif_bitmap_t **bitmap)
{
    nsgif_error ret;
    uint32_t start_frame, f;

    // Validate frame index
    if (frame >= gif->info.frame_count) {
        return NSGIF_ERR_FRAME_IDX;
    }

    // If the requested frame is already decoded, return it immediately
    if (gif->decoded_frame == frame) {
        *bitmap = gif->frame_image;
        return NSGIF_OK;
    }

    // Determine the starting frame for decoding
    // If the target frame is before the current decoded frame, or no frame has 
    // been decoded yet (-1), restart from the beginning (frame 0).
    // Otherwise, start from the next sequential frame.
    if (gif->decoded_frame >= frame || gif->decoded_frame == (uint32_t)-1) {
        start_frame = 0;
    } else {
        start_frame = nsgif__frame_next(gif, 0, gif->decoded_frame);
    }

    // Decode all frames from start_frame up to the requested frame
    for (f = start_frame; f <= frame; ++f) {
        ret = nsgif__process_frame(gif, f, 1);
        if (ret != NSGIF_OK) {
            return ret;
        }
    }

    *bitmap = gif->frame_image;
    return NSGIF_OK;
}