void decipher(uint32_t *v, const uint32_t *k) {
    uint32_t v0 = v[0];
    uint32_t v1 = v[1];
    uint32_t delta = 0x9E3779B9;
    uint32_t sum = delta * 32; // Initialize sum to delta * number_of_rounds (32)
    
    for (size_t i = 0; i < 32; i++) {
        // Reverse the operations on v1
        v1 -= ((v0 << 4) ^ (v0 >> 5)) + v0 ^ (sum + k[(sum >> 11) & 3]);
        
        sum -= delta;
        
        // Reverse the operations on v0
        v0 -= ((v1 << 4) ^ (v1 >> 5)) + v1 ^ (sum + k[sum & 3]);
    }
    
    v[0] = v0;
    v[1] = v1;
}