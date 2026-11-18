int blake2b_init(struct blake2b_state *S, size_t outlen) {
    struct blake2b_state P;
    int ret;

    // Validate output length: must be between 1 and 64
    if (outlen == 0 || outlen > 64) {
        ret = -1;
    } else {
        // Initialize the parameter block P
        P.digest_length = (uint8_t)outlen;
        P.key_length = 0;
        P.fanout = 1;
        P.depth = 1;
        
        // Zero out 32-bit fields
        P.leaf_length = 0;
        P.node_offset = 0;
        
        // Zero out 8-bit fields
        P.node_depth = 0;
        P.inner_length = 0;
        
        // Zero out reserved and salt/personal arrays
        memset(P.reserved, 0, 14);
        memset(P.salt, 0, 16);
        memset(P.personal, 0, 16);
        
        // Initialize the state S using the parameter block P
        ret = blake2b_init_param(S, &P);
    }

    return ret;
}