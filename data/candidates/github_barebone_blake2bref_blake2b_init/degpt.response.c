int blake2b_init(blake2b_state *state, size_t output_length)
{
    // Validate output length: must be between 1 and 64 bytes inclusive
    if ((output_length == 0) || (0x40 < output_length)) {
        return -1;
    }

    // Initialize the parameter structure with default values
    blake2b_param params[1];
    params[0].digest_length = (uint8_t)output_length; // Set the desired hash output length
    params[0].key_length = '\0';              // No key used (unkeyed hash)
    params[0].fanout = '\x01';                // Sequential mode (not parallel)
    params[0].depth = '\x01';                 // Depth of 1 (sequential, not tree)
    store32(&params[0].leaf_length, 0);       // Leaf length is 0 (not a tree node)
    store32(&params[0].node_offset, 0);       // Node offset is 0 (not a tree node)
    store32(&params[0].xof_length, 0);        // XOF length is 0 (not an XOF mode)
    params[0].node_depth = '\0';              // Node depth is 0 (not a tree node)
    params[0].inner_length = '\0';            // Inner length is 0 (not a tree node)
    memset(params[0].reserved, 0, 0xe);       // Clear reserved bytes
    memset(params[0].salt, 0, 0x10);          // Clear salt (no salt used)
    memset(params[0].personal, 0, 0x10);      // Clear personalization string

    // Initialize the state using the configured parameters
    return blake2b_init_param(state, params);
}