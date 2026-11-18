int blake2b_init(void *state, unsigned long long outlen) {
    blake2b_param param;

    // Check for null state pointer
    if (state == NULL) {
        return -1;
    }

    // Validate output length (must be non-zero and <= 64)
    if (outlen == 0 || outlen > 64) {
        blake2b_invalidate_state(state);
        return -1;
    }

    // Initialize parameter block fields
    param.digest_length = (uint8_t)outlen; // -0x58(%rbp)
    param.key_length = 0;                 // -0x57(%rbp)
    param.fanout = 1;                     // -0x56(%rbp)
    param.depth = 1;                      // -0x55(%rbp)
    param.leaf_length = 0;                // -0x54(%rbp)
    param.node_offset = 0;                // -0x50(%rbp)
    param.node_depth = 0;                 // -0x48(%rbp)
    param.inner_length = 0;               // -0x47(%rbp)

    // Zero out the rest of the parameter block
    memset(&param.reserved, 0, 14);       // -0x58 + 0x12
    memset(&param.salt, 0, 16);           // -0x58 + 0x20
    memset(&param.personal, 0, 16);       // -0x58 + 0x30

    // Initialize the state using the populated parameter block
    return blake2b_init_param(state, &param);
}