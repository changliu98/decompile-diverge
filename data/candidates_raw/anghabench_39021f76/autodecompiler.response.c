int
bloom_may_contain(
    bloom_element element,
    bloom_mask mask
) {
    return ((element & mask) == 0);
}