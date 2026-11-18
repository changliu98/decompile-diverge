void decrypt(struct tea_block *block, struct tea_key *key) {
    // Load the block into local variables
    uint32_t v0 = block->v0;
    uint32_t v1 = block->v1;
    
    // Load the 128-bit key into local variables
    uint32_t k0 = key->k0;
    uint32_t k1 = key->k1;
    uint32_t k2 = key->k2;
    uint32_t k3 = key->k3;
    
    // Constants
    uint32_t delta = 0x9e3779b9;
    uint32_t sum = 0xc6ef3720; // delta * 32
    
    // 32 rounds of decryption
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= delta;
    }
    
    // Store the decrypted block back
    block->v0 = v0;
    block->v1 = v1;
}