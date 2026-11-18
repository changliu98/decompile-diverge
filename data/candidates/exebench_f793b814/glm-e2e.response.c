void TEA_transform(uint32_t *v, uint32_t *k) {
    uint32_t v0 = v[0];
    uint32_t v1 = v[1];
    uint32_t k0 = k[0];
    uint32_t k1 = k[1];
    uint32_t k2 = k[2];
    uint32_t k3 = k[3];
    uint32_t sum = 0;
    int i = 16;
    
    do {
        sum += 0x9e3779b9;
        
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        
        i--;
    } while (i != 0);
    
    v[0] += v0;
    v[1] += v1;
}