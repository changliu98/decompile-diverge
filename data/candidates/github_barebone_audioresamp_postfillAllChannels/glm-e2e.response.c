void postfillAllChannels(struct ChannelState *state) {
    int space = state->buffer_size - state->write_idx;

    // Check if space is less than half of period_size
    if (space < state->period_size / 2) {
        // Move existing data to the beginning of the buffer
        for (int i = 0; i < state->num_channels; i++) {
            memmove(state->channels[i],
                    state->channels[i] + state->buffer_size - state->period_size,
                    state->period_size * sizeof(float));
        }

        // Update time remaining
        state->time_remaining -= (double)(state->buffer_size - state->period_size);

        // Update write index
        state->write_idx = state->write_idx - (state->buffer_size - state->period_size);
    }

    // Zero out the remaining space in the buffer
    for (int i = 0; i < state->num_channels; i++) {
        memset(state->channels[i] + state->write_idx,
               0,
               (state->buffer_size - state->write_idx) * sizeof(float));
    }

    // Set the 0x200 flag bit
    state->flags |= 0x200;

    // Advance write index by half of period_size
    state->write_idx += state->period_size / 2;
}