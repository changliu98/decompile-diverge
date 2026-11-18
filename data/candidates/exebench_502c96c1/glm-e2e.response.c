void encipher(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0];
    uint32_t v1 = v[1];
    uint32_t sum = 0;
    uint32_t delta = 0x9e3779b9;
    
    for (int i = 0; i < 32; i++) {
        v0 += ((v1 << 4) ^ (v1 >> 5)) + v1 ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += ((v0 << 4) ^ (v0 >> 5)) + v0 ^ (sum + key[(sum >> 11) & 3]);
    }
    
    v[0] = v0;
    v[1] = v1;
}