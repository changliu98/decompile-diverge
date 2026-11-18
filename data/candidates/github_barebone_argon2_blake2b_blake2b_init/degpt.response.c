int blake2b_init(blake2b_state *state, size_t output_length)
{
    // Check if the state pointer is valid
    if (state == NULL) {
        return -1;
    }
    // Validate output length: must be between 1 and 64 bytes (0x40)
    if (output_length == 0 || output_length > 0x40) {
        // Invalidate the state if parameters are invalid
        blake2b_invalidate_state(state);
        return -1;
    }

    // Initialize the parameter structure with default values
    blake2b_param params;
    params.digest_length = (uint8_t)output_length; // Set the desired output digest length
    params.key_length = 0;                  // No key used (unkeyed hash)
    params.fanout = 1;                      // Sequential hash mode
    params.depth = 1;                       // Single layer (not a tree hash)
    params.leaf_length = 0;                 // Not applicable for sequential mode
    params.node_offset = 0;                 // Not applicable for sequential mode
    params.node_depth = 0;                  // Not applicable for sequential mode
    params.inner_length = 0;                // Not applicable for sequential mode
    memset(params.reserved, 0, 0xe);        // Clear reserved bytes
    memset(params.salt, 0, 0x10);           // Clear salt (no personalization/salt)
    memset(params.personal, 0, 0x10);       // Clear personalization string

    // Initialize the state using the configured parameters
    return blake2b_init_param(state, &params);
}