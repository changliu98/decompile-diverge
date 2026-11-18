void tea_decrypt(struct block *b, const struct key *k) {
    uint64_t v0 = b->v0;
    uint64_t v1 = b->v1;
    
    // 0xc6ef3720 is the sum after 32 forward rounds of adding 0x9e3779b9
    uint64_t sum = 0xc6ef3720;
    uint64_t delta = 0x9e3779b9;
    
    uint64_t k0 = k->k0;
    uint64_t k1 = k->k1;
    uint64_t k2 = k->k2;
    uint64_t k3 = k->k3;
    
    for (int i = 0; i < 32; i++) {
        // v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        
        // v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        
        sum -= delta;
    }
    
    b->v0 = v0;
    b->v1 = v1;
}