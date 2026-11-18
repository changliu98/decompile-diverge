static int set_enlarge(struct ring *ring) {
    struct ring_buffer_event *event = ring->overwrite;
    unsigned int head = ring->head;
    unsigned int tail = ring->tail;
    ring->tail++;
    if (!ring_full(ring)) {
        ring->overwrite = event;
        ring->head = head;
        ring->tail = tail;
        return 0;
    }
    for (unsigned int i = 0;; i++) {
        struct ring_buffer_event *old;
        if (i >= head) {
            old = event;
            if (old) {
                struct ring_buffer_event *next = old->prev;
                unsigned int index = hash_32(old->type_len_time, ring->buffer);
                old->prev = ring->buffer->entries[index];
                ring->buffer->entries[index] = old;
                event = next;
            } else {
                break;
            }
        }
    }
    free(event);
    return 1;
}