int nsgif_frame_decode(struct nsgif *gif, uint32_t frame, struct bitmap **bitmap) {
    int ret = 0;
    uint32_t loop_frame;

    // Check if the requested frame is out of bounds
    if (frame >= gif->frame_count) {
        return 3;
    }

    // If the requested frame is already the current decoded frame, return it
    if (gif->current_frame == frame) {
        *bitmap = gif->bitmap;
        return 0;
    }

    // If the current frame is ahead of the requested frame, or if it's uninitialized (-1)
    if (gif->current_frame < frame || gif->current_frame == 0xFFFFFFFF) {
        loop_frame = 0;
    } else {
        // Find the next frame to start decoding from
        loop_frame = nsgif__frame_next(gif, 0, gif->current_frame);
    }

    // Decode frames sequentially up to the requested frame
    while (loop_frame <= frame) {
        ret = nsgif__process_frame(gif, loop_frame, 1);
        if (ret != 0) {
            return ret;
        }
        loop_frame++;
    }

    // Update the output bitmap pointer and return the final status
    *bitmap = gif->bitmap;
    return ret;
}