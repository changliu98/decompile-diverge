void arx_bwd(uint8_t *state) {
    // 1. Rotate state[2] right by 4 bits
    state[2] = (state[2] >> 4) | (state[2] << 4);

    // 2. XOR state[1] with state[2]
    state[1] ^= state[2];

    // 3. XOR state[3] with state[0]
    state[3] ^= state[0];

    // 4. Rotate state[1] right by 3 bits
    state[1] = (state[1] >> 3) | (state[1] << 5);

    // 5. Rotate state[3] right by 7 bits
    state[3] = (state[3] >> 7) | (state[3] << 1);

    // 6. Subtract state[3] from state[0]
    state[0] -= state[3];

    // 7. Subtract state[1] from state[2]
    state[2] -= state[1];

    // 8. Rotate state[0] right by 4 bits
    state[0] = (state[0] >> 4) | (state[0] << 4);

    // 9. XOR state[1] with state[0]
    state[1] ^= state[0];

    // 10. XOR state[3] with state[2]
    state[3] ^= state[2];

    // 11. Rotate state[1] right by 2 bits
    state[1] = (state[1] >> 2) | (state[1] << 6);

    // 12. Rotate state[3] right by 5 bits
    state[3] = (state[3] >> 5) | (state[3] << 3);

    // 13. Subtract state[1] from state[0]
    state[0] -= state[1];

    // 14. Subtract state[3] from state[2]
    state[2] -= state[3];
}