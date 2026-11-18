int32_t read_image(struct gif_state *state) {
    int32_t ret;
    uint8_t packed_fields;
    int32_t has_transparency;
    uint16_t clamped_w;
    uint16_t clamped_h;

    state->left = read_uint16(state->file);
    state->top = read_uint16(state->file);

    if (state->left >= state->width || state->top >= state->height) {
        return -1;
    }

    state->w = read_uint16(state->file);
    state->h = read_uint16(state->file);

    // Clamp width
    if (state->w < state->width - state->left) {
        clamped_w = state->w;
    } else {
        clamped_w = state->width - state->left;
    }
    state->w = clamped_w;

    // Clamp height
    if (state->h < state->height - state->top) {
        clamped_h = state->h;
    } else {
        clamped_h = state->height - state->top;
    }
    state->h = clamped_h;

    read(state->file, &packed_fields, 1);

    has_transparency = packed_fields & 0x40;

    if (packed_fields & 0x80) { // Local color table flag
        // Size of local color table: 3 * 2^(LCT_size + 1)
        state->palette_size = 1 << ((packed_fields & 0x07) + 1);
        // Allocate and assign local color table
        state->frame_buf = malloc((uint64_t)state->palette_size * 3);
    } else {
        // Use global color table
        state->frame_buf = &state->palette[0];
    }

    ret = read_image_data(state, has_transparency);
    return ret;
}