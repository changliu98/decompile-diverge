void murmur3_init_hash(void *state) {
    *(unsigned int *)state = 0x10;
}