uint16_t handle_to_chunks(uint64_t handle) {
    return (uint16_t)((handle & ~PAGE_MASK) >> BUDDY_SHIFT);
}