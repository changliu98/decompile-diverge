int
all_bits_clear(
    bloom_element element,
    bloom_mask mask
) {
    return ((element & mask) == 0);
}